#include "i2c.h"

static int busy_flag;
static uint8_t *tx_data, tx_byte_count;
static uint8_t *rx_data, rx_byte_count;
static int tx_stop_flag, nack_flag;

void init_i2c(void)
{
    // I2C init
    PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs
    P1MAP3 = PM_UCB0SDA;                      // Map UCB0SDA output to P1.3
    P1MAP2 = PM_UCB0SCL;                      // Map UCB0SCL output to P1.2
    PMAPPWD = 0;                              // Lock port mapping registers

    P1SEL |= BIT2 + BIT3;                     // Select P1.2 & P1.3 to I2C function

    UCB0CTL1 |= UCSWRST;                      // Enable SW reset
    UCB0CTL0 = UCMST | UCMODE_3 | UCSYNC;     // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2 | UCSWRST;            // Use SMCLK, keep SW reset
    UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
    UCB0BR1 = 0;
    UCB0I2CSA = 0x77;                         // Slave Address is 048h
    UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
    //UCB0IE |= UCRXIE;                         // Enable RX interrupt


    /* enable receive and transmit interrupts */
    UCB0IE |= UCTXIE | UCRXIE;
    /* disable STOP, START, arbitration lost interrupts */
    UCB0IE &= ~(UCSTPIE | UCSTTIE | UCALIE);
    /* enable NACK interrupt */
    UCB0IE |= UCNACKIE;

    busy_flag = 0;
    nack_flag = 0;
}

int i2c_busy(void)
{
    return busy_flag;
}

int i2c_nack_received(void)
{
    return nack_flag;
}

void i2c_write(uint8_t slave_addr, uint8_t *data, int count, int stop)
{
    tx_data = data;
    tx_byte_count = count;
    tx_stop_flag = stop;

    busy_flag = 1;
    nack_flag = 0;

    /* set slave address */
    UCB0I2CSA = slave_addr;
    /* select transmitter mode */
    UCB0CTL1 |= UCTR;
    /* generate START condition and transmit slave address */
    UCB0CTL1 |= UCTXSTT;

    /* wait for slave to acknowledge address */
    //while (UCB0CTL1 & UCTXSTT);
    while(busy_flag);
}

void i2c_read(uint8_t slave_addr, uint8_t *data, int count)
{
    rx_data = data;

    busy_flag = 1;
    nack_flag = 0;

    /* set slave address */
    UCB0I2CSA = slave_addr;
    /* select receiver mode */
    UCB0CTL1 &= ~UCTR;

    if (count == 1) {
        rx_byte_count = 0;

        /* generate START condition and transmit slave address */
        UCB0CTL1 |= UCTXSTT;
        /* wait for slave to acknowledge address */
        while (UCB0CTL1 & UCTXSTT)
            ;
        /* generate STOP condition */
        UCB0CTL1 |= UCTXSTP;
    } else {
        rx_byte_count = count - 1;

        /* generate START condition and transmit slave address */
        UCB0CTL1 |= UCTXSTT;
    }

    while(busy_flag);
}

#pragma vector = USCI_B0_VECTOR
__interrupt void USCIAB1TX_ISR (void)
{
    switch(__even_in_range(UCB0IV,12))
    {
        case  0: break;                           // Vector  0: No interrupts
        case  2: break;                           // Vector  2: ALIFG
        case  4:                            // Vector  4: NACKIFG
            /* check for NACK sent by slave */
            //if (UCB0IFG & UCNACKIFG)
            {
                nack_flag = 1;
                /* reset NACK interrupt flag */
                UCB0IFG &= ~UCNACKIFG;
                /* generate STOP condition */
                UCB0CTL1 |= UCTXSTP;
                /* wait until STOP has been sent */
                while (UCB0CTL1 & UCTXSTP)
                    ;
                busy_flag = 0;
            }
            break;
        case  6: break;                           // Vector  6: STTIFG
        case  8: break;                           // Vector  8: STPIFG
        case 10:                                  // Vector 10: RXIFG
          /* check if byte was received */
              //if (UCB0IFG & UCRXIFG)
              {
                  /* last byte? */
                  if (rx_byte_count == 0) {
                      /* get data from receive buffer */
                      *rx_data = UCB0RXBUF;
                      busy_flag = 0;
                  } else {
                      /* second to last byte? */
                      if (rx_byte_count == 1) {
                          /* generate STOP after reception of last byte */
                          UCB0CTL1 |= UCTXSTP;
                      }
                      /* get data */
                      *rx_data++ = UCB0RXBUF;
                      --rx_byte_count;
                  }
              }
          break;
        case 12:
            /* transmit buffer empty? */
                //if (UCB0IFG & UCTXIFG)
                {
                    if (tx_byte_count--) {
                        /* load data into TX buffer */
                        UCB0TXBUF = *tx_data++;
                    } else {
                        /* reset TX interrupt flag */
                        UCB0IFG &= ~UCTXIFG;
                        if (tx_stop_flag) {
                            /* generate STOP condition */
                            UCB0CTL1 |= UCTXSTP;
                            /* wait until STOP has been sent */
                            while (UCB0CTL1 & UCTXSTP)
                                ;
                        }
                        busy_flag = 0;
                    }
                }
                break;                           // Vector 12: TXIFG
        default: break;
    }
}

void rx_interrupt(void)
{
    /* check for NACK sent by slave */
    if (UCB0IFG & UCNACKIFG) {
        nack_flag = 1;
        /* reset NACK interrupt flag */
        UCB0IFG &= ~UCNACKIFG;
        /* generate STOP condition */
        UCB0CTL1 |= UCTXSTP;
        /* wait until STOP has been sent */
        while (UCB0CTL1 & UCTXSTP)
            ;
        busy_flag = 0;
    }
}

void tx_interrupt(void)
{
    /* transmit buffer empty? */
    if (UCB0IFG & UCTXIFG) {
        if (tx_byte_count--) {
            /* load data into TX buffer */
            UCB0TXBUF = *tx_data++;
        } else {
            /* reset TX interrupt flag */
            UCB0IFG &= ~UCTXIFG;
            if (tx_stop_flag) {
                /* generate STOP condition */
                UCB0CTL1 |= UCTXSTP;
                /* wait until STOP has been sent */
                while (UCB0CTL1 & UCTXSTP)
                    ;
            }
            busy_flag = 0;
        }
    }

    /* check if byte was received */
    if (UCB0IFG & UCRXIFG) {
        /* last byte? */
        if (rx_byte_count == 0) {
            /* get data from receive buffer */
            *rx_data = UCB0RXBUF;
            busy_flag = 0;
        } else {
            /* second to last byte? */
            if (rx_byte_count == 1) {
                /* generate STOP after reception of last byte */
                UCB0CTL1 |= UCTXSTP;
            }
            /* get data */
            *rx_data++ = UCB0RXBUF;
            --rx_byte_count;
        }
    }
}
