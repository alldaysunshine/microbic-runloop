
TARGET := --target=armv6m-none-eabi -mcpu=cortex-m4 -mthumb

CPP_FLAGS := -Wall -fno-exceptions -fno-rtti

CRT=-lcrt0
CRT_SEMIHOST=-lcrt0-hosted  -lsemihost

LDD_FLAGS := $(CRT) $(CRT_SEMIHOST)

CLANG := /Applications/LLVMEmbeddedToolchainForArm-17.0.1-Darwin/bin/clang++

OBJ_COPY := /Applications/LLVMEmbeddedToolchainForArm-17.0.1-Darwin/bin/llvm-objcopy
  

LEDDisplay.o: LEDDisplay.cc
	$(CLANG) $(TARGET) $(CPP_FLAGS) -g -c -o LEDDisplay.o LEDDisplay.cc

UART.o: UART.cc
	$(CLANG) $(TARGET) $(CPP_FLAGS) -g -c -o UART.o UART.cc

Button.o: Button.cc
	$(CLANG) $(TARGET) $(CPP_FLAGS) -g -c -o Button.o Button.cc

SysTick.o: SysTick.cc
	$(CLANG) $(TARGET) $(CPP_FLAGS) -g -c -o SysTick.o SysTick.cc

main.o: main.cc
	$(CLANG) $(TARGET) $(CPP_FLAGS) -g -c -o main.o main.cc

RunLoop.o: RunLoop.cc
	$(CLANG) $(TARGET) $(CPP_FLAGS) -g -c -o RunLoop.o RunLoop.cc

Observer.o: Observer.cc
	$(CLANG) $(TARGET) $(CPP_FLAGS) -g -c -o Observer.o Observer.cc

Source.o: Source.cc
	$(CLANG) $(TARGET) $(CPP_FLAGS) -g -c -o Source.o Source.cc

InterruptHandler.o: InterruptHandler.cc
	$(CLANG) $(TARGET) $(CPP_FLAGS) -g -c -o InterruptHandler.o InterruptHandler.cc

ButtonSource.o: ButtonSource.cc
	$(CLANG) $(TARGET) $(CPP_FLAGS) -g -c -o ButtonSource.o ButtonSource.cc

Timer.o: Timer.cc
	$(CLANG) $(TARGET) $(CPP_FLAGS) -g -c -o Timer.o Timer.cc

unit.o: unit.s
	$(CLANG) $(TARGET) $(CPP_FLAGS) -g -c -o unit.o unit.s
	
main.elf: main.o unit.o LEDDisplay.o SysTick.o UART.o Button.o RunLoop.o Source.o Observer.o InterruptHandler.o ButtonSource.o Timer.o
	$(CLANG) $(TARGET) $(LDD_FLAGS) -T main.ld -o main.elf main.o unit.o LEDDisplay.o UART.o SysTick.o Button.o RunLoop.o Source.o Observer.o InterruptHandler.o ButtonSource.o Timer.o

main.hex: main.elf
	$(OBJ_COPY) -O ihex $< $@

run: main.hex
	cp main.hex /Volumes/MICROBIT/

debug: 
	openocd -f interface/cmsis-dap.cfg -f target/nrf51.cfg
	# program sample.hex verify reset

debug-client:
	/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-gdb main.elf
	#target remote localhost:3333

screen: 
	picocom /dev/cu.usbmodem14102 -b 9600

clean:
	rm -f *.hex *.elf *.bin *.map *.o

.PHONY: clean run screen debug
