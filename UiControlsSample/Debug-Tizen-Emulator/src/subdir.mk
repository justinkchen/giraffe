################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AnimationForm.cpp \
../src/BaseForm.cpp \
../src/ButtonForm.cpp \
../src/CheckButtonForm.cpp \
../src/ColorPickerForm.cpp \
../src/CustomButton.cpp \
../src/CustomButtonForm.cpp \
../src/DateTimeForm.cpp \
../src/EditForm.cpp \
../src/EnrichedTextForm.cpp \
../src/ExpandableEditAreaForm.cpp \
../src/FormFactory.cpp \
../src/GalleryForm.cpp \
../src/GroupedListViewForm.cpp \
../src/IconListViewForm.cpp \
../src/ListViewForm.cpp \
../src/MainForm.cpp \
../src/MenuForm.cpp \
../src/MsgBoxPopupForm.cpp \
../src/NavigationForm.cpp \
../src/OverlayKeypadForm.cpp \
../src/PanelForm.cpp \
../src/ProgressForm.cpp \
../src/QuickPanelFrameForm.cpp \
../src/SceneRegister.cpp \
../src/SearchBarForm.cpp \
../src/SliderForm.cpp \
../src/SplitPanelForm.cpp \
../src/TabBarForm.cpp \
../src/TableViewForm.cpp \
../src/TextBoxForm.cpp \
../src/UiControls.cpp \
../src/UiControlsEntry.cpp 

OBJS += \
./src/AnimationForm.o \
./src/BaseForm.o \
./src/ButtonForm.o \
./src/CheckButtonForm.o \
./src/ColorPickerForm.o \
./src/CustomButton.o \
./src/CustomButtonForm.o \
./src/DateTimeForm.o \
./src/EditForm.o \
./src/EnrichedTextForm.o \
./src/ExpandableEditAreaForm.o \
./src/FormFactory.o \
./src/GalleryForm.o \
./src/GroupedListViewForm.o \
./src/IconListViewForm.o \
./src/ListViewForm.o \
./src/MainForm.o \
./src/MenuForm.o \
./src/MsgBoxPopupForm.o \
./src/NavigationForm.o \
./src/OverlayKeypadForm.o \
./src/PanelForm.o \
./src/ProgressForm.o \
./src/QuickPanelFrameForm.o \
./src/SceneRegister.o \
./src/SearchBarForm.o \
./src/SliderForm.o \
./src/SplitPanelForm.o \
./src/TabBarForm.o \
./src/TableViewForm.o \
./src/TextBoxForm.o \
./src/UiControls.o \
./src/UiControlsEntry.o 

CPP_DEPS += \
./src/AnimationForm.d \
./src/BaseForm.d \
./src/ButtonForm.d \
./src/CheckButtonForm.d \
./src/ColorPickerForm.d \
./src/CustomButton.d \
./src/CustomButtonForm.d \
./src/DateTimeForm.d \
./src/EditForm.d \
./src/EnrichedTextForm.d \
./src/ExpandableEditAreaForm.d \
./src/FormFactory.d \
./src/GalleryForm.d \
./src/GroupedListViewForm.d \
./src/IconListViewForm.d \
./src/ListViewForm.d \
./src/MainForm.d \
./src/MenuForm.d \
./src/MsgBoxPopupForm.d \
./src/NavigationForm.d \
./src/OverlayKeypadForm.d \
./src/PanelForm.d \
./src/ProgressForm.d \
./src/QuickPanelFrameForm.d \
./src/SceneRegister.d \
./src/SearchBarForm.d \
./src/SliderForm.d \
./src/SplitPanelForm.d \
./src/TabBarForm.d \
./src/TableViewForm.d \
./src/TextBoxForm.d \
./src/UiControls.d \
./src/UiControlsEntry.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: C++ Compiler'
	clang++.exe -I"pch" -D_DEBUG -I"C:\Users\Justin\Dropbox\CS210\unsamsung\UiControlsSample\inc" -O0 -g3 -Wall -c -fmessage-length=0 -target i386-tizen-linux-gnueabi -gcc-toolchain C:/tizen-sdk/tools/smart-build-interface/../i386-linux-gnueabi-gcc-4.5/ -ccc-gcc-name i386-linux-gnueabi-g++ -march=i386 -Wno-gnu -fPIE --sysroot="C:/tizen-sdk/platforms/tizen2.0/rootstraps/tizen-emulator-2.0.cpp" -I"C:/tizen-sdk/platforms/tizen2.0/rootstraps/tizen-emulator-2.0.cpp/usr/include" -I"C:/tizen-sdk/platforms/tizen2.0/rootstraps/tizen-emulator-2.0.cpp/usr/include/libxml2" -I"C:\tizen-sdk\library" -I"C:/tizen-sdk/platforms/tizen2.0/rootstraps/tizen-emulator-2.0.cpp/usr/include/osp" -D_APP_LOG -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


