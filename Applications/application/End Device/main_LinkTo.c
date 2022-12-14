/*----------------------------------------------------------------------------
 *  Demo Application for SimpliciTI 
 * 
 *  L. Friedman 
 *  Texas Instruments, Inc.
 *---------------------------------------------------------------------------- */

/********************************************************************************************
  Copyright 2007-2009 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights granted under
  the terms of a software license agreement between the user who downloaded the software,
  his/her employer (which must be your employer) and Texas Instruments Incorporated (the
  "License"). You may not use this Software unless you agree to abide by the terms of the
  License. The License limits your use, and you acknowledge, that the Software may not be
  modified, copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio frequency
  transceiver, which is integrated into your product. Other than for the foregoing purpose,
  you may not use, reproduce, copy, prepare derivative works of, modify, distribute,
  perform, display or sell this Software and/or its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE PROVIDED ?AS IS?
  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY
  WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
  IN NO EVENT SHALL TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE
  THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY
  INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST
  DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY
  THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/

#include "bsp.h"
#include "mrfi.h"
#include "nwk_types.h"
#include "nwk_api.h"
#include "bsp_leds.h"
#include "bsp_buttons.h"

#include "../app_remap_led.h"

#include "i2c.h"

#include "bme280.h"
#include "timer.h"
#include "adc.h"

#define RADIO_UNLINKED              0
#define RADIO_LINKED                0xFF


static void linkTo(void);

void toggleLED(uint8_t);

static uint8_t  sTxTid=0, sRxTid=0;
static linkID_t sLinkID1 = 0;

/* application Rx frame handler. */
static uint8_t sRxCallback(linkID_t);

#define SPIN_ABOUT_A_SECOND  NWK_DELAY(1000)

uint8_t i2c_buf[4];
int32_t temp;
int32_t pressure;
uint32_t hum;
int16_t int_temp;
smplStatus_t stat;
uint8_t  msg[10];

uint8_t radio_state = RADIO_UNLINKED;

void main (void)
{
    uint8_t i;

    BSP_Init();

    init_i2c();

    adc_Init();

    __enable_interrupt();

    //i2c_buf[0] = 0xD0;
    //i2c_write(0x76, i2c_buf, 1, 0);
    //i2c_read(0x76, i2c_buf, 2);

    bme280_init();

    Timer1_Init();

    /* If an on-the-fly device address is generated it must be done before the
    * call to SMPL_Init(). If the address is set here the ROM value will not
    * be used. If SMPL_Init() runs before this IOCTL is used the IOCTL call
    * will not take effect. One shot only. The IOCTL call below is conformal.
    */
#ifdef I_WANT_TO_CHANGE_DEFAULT_ROM_DEVICE_ADDRESS_PSEUDO_CODE
  {
    addr_t lAddr;

    createRandomAddress(&lAddr);
    SMPL_Ioctl(IOCTL_OBJ_ADDR, IOCTL_ACT_SET, &lAddr);
  }
#endif /* I_WANT_TO_CHANGE_DEFAULT_ROM_DEVICE_ADDRESS_PSEUDO_CODE */

    /* This call will fail because the join will fail since there is no Access Point
    * in this scenario. But we don't care -- just use the default link token later.
    * We supply a callback pointer to handle the message returned by the peer.
    */
    SMPL_Init(sRxCallback);

    /* turn on LEDs. */
    BSP_TURN_ON_LED1();
    Timer1_A4_Delay( CONV_MS_TO_TICKS(1000) );

    BSP_TURN_ON_LED2();
    Timer1_A4_Delay( CONV_MS_TO_TICKS(1000) );

    BSP_TURN_OFF_LED1();
    Timer1_A4_Delay( CONV_MS_TO_TICKS(1000) );

    BSP_TURN_OFF_LED2();
    Timer1_A4_Delay( CONV_MS_TO_TICKS(1000) );

#if 0
  // ????? ???????????? ???????? ???????????? ? ????? ???????/??????? ??????????
  while (SMPL_SUCCESS != SMPL_Link(&sLinkID1))
    {
    /* blink LEDs until we link successfully */
    toggleLED(1);
    toggleLED(2);
    //SPIN_ABOUT_A_SECOND;

    Timer1_A4_Delay( CONV_MS_TO_TICKS(1000) );
    }
#endif

  // ????????? ?????? ??? ?? 1 ???????
  // ? ??? ??????????? ?????? ????? (???????? ?????? ??????????? 15 ?????)
  // ????????? ??????? bmp, ???????? ??? ??????? ( ????? ?????????)
  // ??????????? ??????????
  // ???????? ?????? ?? ????? ???????
  // ??? ???? ?????????? ??????? ?????? ????
  while(1)
  {
      //for()
      BSP_TURN_ON_LED1();
      temp = bme280_readTemperature();
      pressure = bme280_readPressure();
      hum = bme280_readHumidity();

      int_temp = adc_GetRawTemp();

      BSP_TURN_OFF_LED1();


      memcpy(msg, &temp, sizeof(temp));
      memcpy(msg + 4, &pressure, 3);
      msg[7] = hum;

      memcpy(msg + 8, &int_temp, 2);

      //uint8_t  msg[8];
      //stat = SMPL_Send(sLinkID1, msg, sizeof(msg));
      switch(radio_state)
      {
          case RADIO_UNLINKED:
                BSP_TURN_OFF_LED1();
                BSP_TURN_OFF_LED2();

                for(i = 0; i < 4; i++)
                {
                    if(SMPL_SUCCESS != SMPL_Link(&sLinkID1))
                    {
                        /* blink LEDs until we link successfully */
                        toggleLED(1);
                        toggleLED(2);
                        BSP_to_lpm();
                    }
                    else
                    {
                        BSP_TURN_OFF_LED1();
                        BSP_TURN_OFF_LED2();

                        radio_state = RADIO_LINKED;

                        SMPL_SendOpt(sLinkID1, msg, sizeof(msg), SMPL_TXOPTION_ACKREQ);
                        break;
                    }
                }
                break;

          case RADIO_LINKED:
                // ?????? ??? ??????? ???????? ??????
                for(i = 0; i < 3; i++)
                {
                    BSP_TURN_ON_LED3();
                    //? ?????? ?????????? ??????/????????????? ???????? ?? 1 ???????
                    if(SMPL_SendOpt(sLinkID1, msg, sizeof(msg), SMPL_TXOPTION_ACKREQ) == SMPL_NO_ACK)
                    {
                        BSP_TURN_OFF_LED3();
                        BSP_to_lpm();
                    }
                    else
                    {
                        BSP_TURN_OFF_LED3();

                        //????? ?? ?????
                        break;
                    }
                }

                if(i >= 3)
                {
                    //unlink
                    SMPL_UnlinkForced(sLinkID1);
                    radio_state = RADIO_UNLINKED;
                }
                break;
      }//switch

      //???
      for(i = 0; i < 15; i++)
          BSP_to_lpm();
  }
  /* never coming back... */
  //linkTo();

  /* but in case we do... */
  while (1) ;
}

static void linkTo()
{
  uint8_t  msg[2], delay = 0;

  while (SMPL_SUCCESS != SMPL_Link(&sLinkID1))
  {
    /* blink LEDs until we link successfully */
    toggleLED(1);
    toggleLED(2);
    //SPIN_ABOUT_A_SECOND;

    Timer1_A4_Delay( CONV_MS_TO_TICKS(1000) );
  }

  /* we're linked. turn off red LED. received messages will toggle the green LED. */
  if (BSP_LED2_IS_ON())
  {
    toggleLED(2);
  }

  /* turn on RX. default is RX off. */
  SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXON, 0);

  /* put LED to toggle in the message */
  msg[0] = 2;  /* toggle red */
  while (1)
  {
    SPIN_ABOUT_A_SECOND;
    if (delay > 0x00)
    {
      SPIN_ABOUT_A_SECOND;
    }
    if (delay > 0x01)
    {
      SPIN_ABOUT_A_SECOND;
    }
    if (delay > 0x02)
    {
      SPIN_ABOUT_A_SECOND;
    }

    /* delay longer and longer -- then start over */
    delay = (delay+1) & 0x03;
    /* put the sequence ID in the message */
    msg[1] = ++sTxTid;
    SMPL_Send(sLinkID1, msg, sizeof(msg));


    // ????????? ??????????? ??? ? ??????
    temp = bme280_readTemperature();
    pressure = bme280_readPressure();
    hum = bme280_readHumidity();


  }
}


void toggleLED(uint8_t which)
{
  if (1 == which)
  {
    BSP_TOGGLE_LED1();
  }
  else if (2 == which)
  {
    BSP_TOGGLE_LED2();
  }
  return;
}

/* handle received frames. */
static uint8_t sRxCallback(linkID_t port)
{
  uint8_t msg[2], len, tid;

  /* is the callback for the link ID we want to handle? */
  if (port == sLinkID1)
  {
    /* yes. go get the frame. we know this call will succeed. */
     if ((SMPL_SUCCESS == SMPL_Receive(sLinkID1, msg, &len)) && len)
     {
       /* Check the application sequence number to detect
        * late or missing frames... 
        */
       tid = *(msg+1);
       if (tid)
       {
         if (tid > sRxTid)
         {
           /* we're good. toggle LED in the message */
           toggleLED(*msg);
           sRxTid = tid;
         }
       }
       else
       {
         /* the wrap case... */
         if (sRxTid)
         {
           /* we're good. toggle LED in the message */
           toggleLED(*msg);
           sRxTid = tid;
         }
       }
       /* drop frame. we're done with it. */
       return 1;
     }
  }
  /* keep frame for later handling. */
  return 0;
}

