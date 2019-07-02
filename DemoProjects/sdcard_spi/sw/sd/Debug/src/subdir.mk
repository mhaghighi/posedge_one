################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ff.c \
../src/helloworld.c \
../src/ma_delay.c \
../src/ma_ff_timer.c \
../src/ma_sd_gpio.c \
../src/sdmm.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/ff.o \
./src/helloworld.o \
./src/ma_delay.o \
./src/ma_ff_timer.o \
./src/ma_sd_gpio.o \
./src/sdmm.o 

C_DEPS += \
./src/ff.d \
./src/helloworld.d \
./src/ma_delay.d \
./src/ma_ff_timer.d \
./src/ma_sd_gpio.d \
./src/sdmm.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../standalone_bsp_0/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


