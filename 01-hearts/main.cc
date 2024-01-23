
#import "AsmBridge.h"

#import <iostream>
#import <string>

#import "LEDDisplay.h"
#import "SysTick.h"
#import "UART.h"
#import "Button.h"

#import "ButtonSource.h"

#import "RunLoop.h"

int bigHeart[5][5] = {
	{ 0, 1, 0, 1, 0},
	{ 1, 1, 1, 1, 1},
	{ 1, 1, 1, 1, 1},
	{ 0, 1, 1, 1, 0},
	{ 0, 0, 1, 0, 0}
};

int smallHeart[5][5] = {
		{ 0, 0, 0, 0, 0},
		{ 0, 1, 0, 1, },
		{ 0, 1, 1, 1, 0},
		{ 0, 0, 1, 0, 0},
		{ 0, 0, 0, 0, 0}
};

SysTick systick; 

LEDDisplay display(systick); 
UART uart; 

Button button; 

RunLoop runloop; 

ButtonSource buttonSource(button); 
Observer observer([](Event * event) {
			if (event->state == 1) {
				runloop.runAfter(0, []() {
					display.set(&bigHeart);
				});
				runloop.runAfter(500, []() {
					display.set(&smallHeart);
				});
				runloop.runAfter(1000, []() {
					display.set(&bigHeart);
				});
				runloop.runAfter(1500, []() {
					display.set(&smallHeart);
				});
			} else {
		//		display.set(&n);
			}
//	uart->transmitString("Button A: ");
	if (event->state == 1) {
	//	uart->transmitString("Pressed\r\n");
	} else {
	//	uart->transmitString("Released\r\n");
	}
}); 


extern "C" void arm_systick_isr() {
	display.strobeNextRow(); 

}

extern "C" void arm_gpiote_isr() {
	buttonSource.handleInterrupt(); 
}


int main(void) {
	display.set(&smallHeart);

	display.enable(); 

	systick.enable();
	uart.enable(); 

	button.enable(); 

	buttonSource.enableInterrupt(); 
	
	runloop.addObserver(observer);
	runloop.addSource(buttonSource);
	
	runloop.run(); 
	 
  	return 0;
}

