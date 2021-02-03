################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o

OBJS_AS_ARGS +=  \
main.o

C_DEPS +=  \
main.d

C_DEPS_AS_ARGS +=  \
main.d

OUTPUT_FILE_PATH +=glcd_test_now_that_i_understand.elf

OUTPUT_FILE_PATH_AS_ARGS +=glcd_test_now_that_i_understand.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./main.o: .././main.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)D:\atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG -DGLCD_DEVICE_AVR8 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -DGLCD_USE_AVR_DELAY -D__DELAY_BACKWARD_COMPATIBLE__  -I"D:\atmel\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"../../../../glcd-master"  -O0 -ffunction-sections -fdata-sections -fpack-struct -mrelax -g2 -Wall -mmcu=atmega1284 -B "D:\atmel\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega1284" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)D:\atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="glcd_test_now_that_i_understand.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mrelax -mmcu=atmega1284 -B "D:\atmel\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega1284"  
	@echo Finished building target: $@
	"D:\atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "glcd_test_now_that_i_understand.elf" "glcd_test_now_that_i_understand.hex"
	"D:\atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "glcd_test_now_that_i_understand.elf" "glcd_test_now_that_i_understand.eep" || exit 0
	"D:\atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "glcd_test_now_that_i_understand.elf" > "glcd_test_now_that_i_understand.lss"
	"D:\atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "glcd_test_now_that_i_understand.elf" "glcd_test_now_that_i_understand.srec"
	"D:\atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "glcd_test_now_that_i_understand.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "glcd_test_now_that_i_understand.elf" "glcd_test_now_that_i_understand.a" "glcd_test_now_that_i_understand.hex" "glcd_test_now_that_i_understand.lss" "glcd_test_now_that_i_understand.eep" "glcd_test_now_that_i_understand.map" "glcd_test_now_that_i_understand.srec" "glcd_test_now_that_i_understand.usersignatures"
	