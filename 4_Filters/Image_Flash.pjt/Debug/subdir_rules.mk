################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
ADC.obj: ../ADC.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" --silicon_version=28 -g --include_path="/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --include_path="/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ADC.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_ADC_cal.obj: ../DSP2833x_ADC_cal.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" --silicon_version=28 -g --include_path="/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --include_path="/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_ADC_cal.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_Adc.obj: ../DSP2833x_Adc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" --silicon_version=28 -g --include_path="/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --include_path="/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_Adc.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_CodeStartBranch.obj: ../DSP2833x_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" --silicon_version=28 -g --include_path="/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --include_path="/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_CodeStartBranch.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_CpuTimers.obj: ../DSP2833x_CpuTimers.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" --silicon_version=28 -g --include_path="/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --include_path="/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_CpuTimers.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_DefaultIsr.obj: ../DSP2833x_DefaultIsr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" --silicon_version=28 -g --include_path="/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --include_path="/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_DefaultIsr.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_GlobalVariableDefs.obj: ../DSP2833x_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" --silicon_version=28 -g --include_path="/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --include_path="/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_GlobalVariableDefs.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_PieCtrl.obj: ../DSP2833x_PieCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" --silicon_version=28 -g --include_path="/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --include_path="/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_PieCtrl.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_PieVect.obj: ../DSP2833x_PieVect.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" --silicon_version=28 -g --include_path="/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --include_path="/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_PieVect.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_SysCtrl.obj: ../DSP2833x_SysCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" --silicon_version=28 -g --include_path="/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --include_path="/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_SysCtrl.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_usDelay.obj: ../DSP2833x_usDelay.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" --silicon_version=28 -g --include_path="/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --include_path="/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_usDelay.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

Image_FLASH_API.obj: ../Image_FLASH_API.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" --silicon_version=28 -g --include_path="/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --include_path="/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="Image_FLASH_API.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

Image_Processing_Functions.obj: ../Image_Processing_Functions.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" --silicon_version=28 -g --include_path="/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --include_path="/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="Image_Processing_Functions.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

Image_main.obj: ../Image_main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/bin/cl2000" --silicon_version=28 -g --include_path="/opt/ti/ccsv6/tools/compiler/c2000_15.12.3.LTS/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --include_path="/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="Image_main.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


