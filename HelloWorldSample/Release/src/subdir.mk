################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/HelloWorld.cpp \
../src/HelloWorldEntry.cpp \
../src/HelloWorldFormFactory.cpp \
../src/HelloWorldFrame.cpp \
../src/HelloWorldMainForm.cpp \
../src/HelloWorldPanelFactory.cpp 

OBJS += \
./src/HelloWorld.o \
./src/HelloWorldEntry.o \
./src/HelloWorldFormFactory.o \
./src/HelloWorldFrame.o \
./src/HelloWorldMainForm.o \
./src/HelloWorldPanelFactory.o 

CPP_DEPS += \
./src/HelloWorld.d \
./src/HelloWorldEntry.d \
./src/HelloWorldFormFactory.d \
./src/HelloWorldFrame.d \
./src/HelloWorldMainForm.d \
./src/HelloWorldPanelFactory.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: C++ Compiler'
	clang++.exe -I"pch" -I"C:\Users\Justin\Dropbox\CS210\unsamsung\HelloWorld\inc" -O3 -g -Wall -c -fmessage-length=0 -target arm-tizen-linux-gnueabi -gcc-toolchain C:/tizen-sdk/tools/smart-build-interface/../arm-linux-gnueabi-gcc-4.5/ -ccc-gcc-name arm-linux-gnueabi-g++ -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -mtune=cortex-a8 -Wno-gnu -fPIE --sysroot="C:/tizen-sdk/platforms/tizen2.0/rootstraps/tizen-device-2.0.cpp" -I"C:/tizen-sdk/platforms/tizen2.0/rootstraps/tizen-device-2.0.cpp/usr/include" -I"C:/tizen-sdk/platforms/tizen2.0/rootstraps/tizen-device-2.0.cpp/usr/include/libxml2" -I"C:\tizen-sdk\library" -I"C:/tizen-sdk/platforms/tizen2.0/rootstraps/tizen-device-2.0.cpp/usr/include/osp" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


