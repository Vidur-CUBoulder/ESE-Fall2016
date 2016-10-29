################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/dma.c \
../Sources/error_handling.c \
../Sources/ftoa.c \
../Sources/log.c \
../Sources/main.c \
../Sources/memory.c \
../Sources/timer.c \
../Sources/uart.c 

OBJS += \
./Sources/dma.o \
./Sources/error_handling.o \
./Sources/ftoa.o \
./Sources/log.o \
./Sources/main.o \
./Sources/memory.o \
./Sources/timer.o \
./Sources/uart.o 

C_DEPS += \
./Sources/dma.d \
./Sources/error_handling.d \
./Sources/ftoa.d \
./Sources/log.d \
./Sources/main.d \
./Sources/memory.d \
./Sources/timer.d \
./Sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


