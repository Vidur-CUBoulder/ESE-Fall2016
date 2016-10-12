################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/circular_buffer.c \
../Sources/circular_buffer_test.c \
../Sources/data.c \
../Sources/ftoa.c \
../Sources/led.c \
../Sources/log.c \
../Sources/main.c \
../Sources/memory.c \
../Sources/timer.c \
../Sources/uart.c 

OBJS += \
./Sources/circular_buffer.o \
./Sources/circular_buffer_test.o \
./Sources/data.o \
./Sources/ftoa.o \
./Sources/led.o \
./Sources/log.o \
./Sources/main.o \
./Sources/memory.o \
./Sources/timer.o \
./Sources/uart.o 

C_DEPS += \
./Sources/circular_buffer.d \
./Sources/circular_buffer_test.d \
./Sources/data.d \
./Sources/ftoa.d \
./Sources/led.d \
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


