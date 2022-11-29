################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./Applications/application/End Device/adc.obj" \
"./Applications/application/End Device/bme280.obj" \
"./Applications/application/End Device/i2c.obj" \
"./Applications/application/End Device/main_LinkTo.obj" \
"./Applications/application/End Device/timer.obj" \
"./Components/bsp/bsp.obj" \
"./Components/mrfi/mrfi.obj" \
"./Components/nwk/nwk.obj" \
"./Components/nwk/nwk_QMgmt.obj" \
"./Components/nwk/nwk_api.obj" \
"./Components/nwk/nwk_frame.obj" \
"./Components/nwk/nwk_globals.obj" \
"./Components/nwk_applications/nwk_freq.obj" \
"./Components/nwk_applications/nwk_ioctl.obj" \
"./Components/nwk_applications/nwk_join.obj" \
"./Components/nwk_applications/nwk_link.obj" \
"./Components/nwk_applications/nwk_mgmt.obj" \
"./Components/nwk_applications/nwk_ping.obj" \
"./Components/nwk_applications/nwk_security.obj" \
"../lnk_cc430f5137.cmd" \
$(GEN_CMDS__FLAG) \
-llibmath.a \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Applications/application/End\ Device/subdir_vars.mk
-include Components/bsp/subdir_vars.mk
-include Components/mrfi/subdir_vars.mk
-include Components/nwk/subdir_vars.mk
-include Components/nwk_applications/subdir_vars.mk
-include subdir_rules.mk
-include Applications/application/End\ Device/subdir_rules.mk
-include Components/bsp/subdir_rules.mk
-include Components/mrfi/subdir_rules.mk
-include Components/nwk/subdir_rules.mk
-include Components/nwk_applications/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
CC430F5137_EndDevice.out \

EXE_OUTPUTS__QUOTED += \
"CC430F5137_EndDevice.out" \

BIN_OUTPUTS += \
CC430F5137_EndDevice.hex \

BIN_OUTPUTS__QUOTED += \
"CC430F5137_EndDevice.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "CC430F5137_EndDevice.out"

# Tool invocations
CC430F5137_EndDevice.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --advice:power=all --define=__CC430F5137__ --define=MRFI_CC430 -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 -z -m"CC430F5137_EndDevice.map" --heap_size=80 --stack_size=80 --cinit_hold_wdt=on -i"C:/ti/ccs1040/ccs/ccs_base/msp430/include" -i"C:/ti/ccs1040/ccs/ccs_base/msp430/lib/5xx_6xx_FRxx" -i"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/lib" -i"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="CC430F5137_EndDevice_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "CC430F5137_EndDevice.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

CC430F5137_EndDevice.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: MSP430 Hex Utility'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/hex430" --memwidth=8 --romwidth=8 --diag_wrap=off -o "CC430F5137_EndDevice.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "Applications\application\End Device\adc.obj" "Applications\application\End Device\bme280.obj" "Applications\application\End Device\i2c.obj" "Applications\application\End Device\main_LinkTo.obj" "Applications\application\End Device\timer.obj" "Components\bsp\bsp.obj" "Components\mrfi\mrfi.obj" "Components\nwk\nwk.obj" "Components\nwk\nwk_QMgmt.obj" "Components\nwk\nwk_api.obj" "Components\nwk\nwk_frame.obj" "Components\nwk\nwk_globals.obj" "Components\nwk_applications\nwk_freq.obj" "Components\nwk_applications\nwk_ioctl.obj" "Components\nwk_applications\nwk_join.obj" "Components\nwk_applications\nwk_link.obj" "Components\nwk_applications\nwk_mgmt.obj" "Components\nwk_applications\nwk_ping.obj" "Components\nwk_applications\nwk_security.obj" 
	-$(RM) "Applications\application\End Device\adc.d" "Applications\application\End Device\bme280.d" "Applications\application\End Device\i2c.d" "Applications\application\End Device\main_LinkTo.d" "Applications\application\End Device\timer.d" "Components\bsp\bsp.d" "Components\mrfi\mrfi.d" "Components\nwk\nwk.d" "Components\nwk\nwk_QMgmt.d" "Components\nwk\nwk_api.d" "Components\nwk\nwk_frame.d" "Components\nwk\nwk_globals.d" "Components\nwk_applications\nwk_freq.d" "Components\nwk_applications\nwk_ioctl.d" "Components\nwk_applications\nwk_join.d" "Components\nwk_applications\nwk_link.d" "Components\nwk_applications\nwk_mgmt.d" "Components\nwk_applications\nwk_ping.d" "Components\nwk_applications\nwk_security.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

