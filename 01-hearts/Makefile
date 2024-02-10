
run: 
	mkdir -p build
	(cd build && cmake ..)
	(cd build && make)
	cp build/hearts.hex /Volumes/MICROBIT/

debug: 
	openocd -f interface/cmsis-dap.cfg -f target/nrf51.cfg
	# program sample.hex verify reset

debug-client:
	/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-gdb main.elf
	#target remote localhost:3333

screen: 
	picocom /dev/cu.usbmodem14202 -b 9600

clean:
	rm -rf build

.PHONY: clean run screen debug
