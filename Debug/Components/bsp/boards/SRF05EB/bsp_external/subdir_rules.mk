################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Components/bsp/boards/SRF05EB/bsp_external/%.obj: ../Components/bsp/boards/SRF05EB/bsp_external/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --include_path="C:/ti/ccs1040/ccs/ccs_base/msp430/include" --include_path="C:/Users/bryki/workspace_v10/CC430F5137_EndDevice" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --include_path="C:/Users/bryki/workspace_v10/CC430F5137_EndDevice/Components/bsp" --include_path="C:/Users/bryki/workspace_v10/CC430F5137_EndDevice/Components/bsp/boards/CC430EM" --include_path="C:/Users/bryki/workspace_v10/CC430F5137_EndDevice/Components/bsp/drivers" --include_path="C:/Users/bryki/workspace_v10/CC430F5137_EndDevice/Components/nwk" --include_path="C:/Users/bryki/workspace_v10/CC430F5137_EndDevice/Components/nwk_applications" --advice:power=all --define=__CC430F5137__ --define=MRFI_CC430 -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="Components/bsp/boards/SRF05EB/bsp_external/$(basename $(<F)).d_raw" --obj_directory="Components/bsp/boards/SRF05EB/bsp_external" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


