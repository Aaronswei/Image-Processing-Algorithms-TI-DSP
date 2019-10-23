################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LIB_SRCS += \
../Flash28335_API_V210.lib 

C_SRCS += \
../ADC.c \
../DSP2833x_Adc.c \
../DSP2833x_CpuTimers.c \
../DSP2833x_DefaultIsr.c \
../DSP2833x_GlobalVariableDefs.c \
../DSP2833x_PieCtrl.c \
../DSP2833x_PieVect.c \
../DSP2833x_SysCtrl.c \
../Image_FLASH_API.c \
../Image_Processing_Functions.c \
../Image_main.c 

ASM_SRCS += \
../DSP2833x_ADC_cal.asm \
../DSP2833x_CodeStartBranch.asm \
../DSP2833x_usDelay.asm 

CMD_SRCS += \
../DSP2833x_Headers_nonBIOS.cmd \
../F28335.cmd 

ASM_DEPS += \
./DSP2833x_ADC_cal.pp \
./DSP2833x_CodeStartBranch.pp \
./DSP2833x_usDelay.pp 

OBJS += \
./ADC.obj \
./DSP2833x_ADC_cal.obj \
./DSP2833x_Adc.obj \
./DSP2833x_CodeStartBranch.obj \
./DSP2833x_CpuTimers.obj \
./DSP2833x_DefaultIsr.obj \
./DSP2833x_GlobalVariableDefs.obj \
./DSP2833x_PieCtrl.obj \
./DSP2833x_PieVect.obj \
./DSP2833x_SysCtrl.obj \
./DSP2833x_usDelay.obj \
./Image_FLASH_API.obj \
./Image_Processing_Functions.obj \
./Image_main.obj 

C_DEPS += \
./ADC.pp \
./DSP2833x_Adc.pp \
./DSP2833x_CpuTimers.pp \
./DSP2833x_DefaultIsr.pp \
./DSP2833x_GlobalVariableDefs.pp \
./DSP2833x_PieCtrl.pp \
./DSP2833x_PieVect.pp \
./DSP2833x_SysCtrl.pp \
./Image_FLASH_API.pp \
./Image_Processing_Functions.pp \
./Image_main.pp 

OBJS__QTD += \
".\ADC.obj" \
".\DSP2833x_ADC_cal.obj" \
".\DSP2833x_Adc.obj" \
".\DSP2833x_CodeStartBranch.obj" \
".\DSP2833x_CpuTimers.obj" \
".\DSP2833x_DefaultIsr.obj" \
".\DSP2833x_GlobalVariableDefs.obj" \
".\DSP2833x_PieCtrl.obj" \
".\DSP2833x_PieVect.obj" \
".\DSP2833x_SysCtrl.obj" \
".\DSP2833x_usDelay.obj" \
".\Image_FLASH_API.obj" \
".\Image_Processing_Functions.obj" \
".\Image_main.obj" 

ASM_DEPS__QTD += \
".\DSP2833x_ADC_cal.pp" \
".\DSP2833x_CodeStartBranch.pp" \
".\DSP2833x_usDelay.pp" 

C_DEPS__QTD += \
".\ADC.pp" \
".\DSP2833x_Adc.pp" \
".\DSP2833x_CpuTimers.pp" \
".\DSP2833x_DefaultIsr.pp" \
".\DSP2833x_GlobalVariableDefs.pp" \
".\DSP2833x_PieCtrl.pp" \
".\DSP2833x_PieVect.pp" \
".\DSP2833x_SysCtrl.pp" \
".\Image_FLASH_API.pp" \
".\Image_Processing_Functions.pp" \
".\Image_main.pp" 

C_SRCS_QUOTED += \
"../ADC.c" \
"../DSP2833x_Adc.c" \
"../DSP2833x_CpuTimers.c" \
"../DSP2833x_DefaultIsr.c" \
"../DSP2833x_GlobalVariableDefs.c" \
"../DSP2833x_PieCtrl.c" \
"../DSP2833x_PieVect.c" \
"../DSP2833x_SysCtrl.c" \
"../Image_FLASH_API.c" \
"../Image_Processing_Functions.c" \
"../Image_main.c" 

ASM_SRCS_QUOTED += \
"../DSP2833x_ADC_cal.asm" \
"../DSP2833x_CodeStartBranch.asm" \
"../DSP2833x_usDelay.asm" 


# Each subdirectory must supply rules for building sources it contributes
ADC.obj: ../ADC.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="ADC.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_ADC_cal.obj: ../DSP2833x_ADC_cal.asm $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_ADC_cal.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_Adc.obj: ../DSP2833x_Adc.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_Adc.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_CodeStartBranch.obj: ../DSP2833x_CodeStartBranch.asm $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_CodeStartBranch.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_CpuTimers.obj: ../DSP2833x_CpuTimers.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_CpuTimers.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_DefaultIsr.obj: ../DSP2833x_DefaultIsr.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_DefaultIsr.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_GlobalVariableDefs.obj: ../DSP2833x_GlobalVariableDefs.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_GlobalVariableDefs.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_PieCtrl.obj: ../DSP2833x_PieCtrl.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_PieCtrl.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_PieVect.obj: ../DSP2833x_PieVect.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_PieVect.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_SysCtrl.obj: ../DSP2833x_SysCtrl.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_SysCtrl.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_usDelay.obj: ../DSP2833x_usDelay.asm $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_usDelay.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Image_FLASH_API.obj: ../Image_FLASH_API.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="Image_FLASH_API.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Image_Processing_Functions.obj: ../Image_Processing_Functions.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="Image_Processing_Functions.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Image_main.obj: ../Image_main.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/tidcs/c28/Flash28_API/Flash28335_API_V210/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_common/include" --include_path="C:/tidcs/c28/DSP2833x/v131/DSP2833x_headers/include" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="Image_main.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


