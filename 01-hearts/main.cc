
#import "AsmBridge.h"

#import <iostream>
#import <string>

#import "LEDDisplay.h"
#import "SysTick.h"
#import "UART.h"
#import "Button.h"

#import "ButtonSource.h"
#import "ButtonObserver.h"

#import "RunLoop.h"

SysTick systick; 

LEDDisplay display(systick); 
UART uart; 

Button button; 

ButtonSource buttonSource(button); 
ButtonObserver observer(display, uart); 

RunLoop runloop; 

extern "C" void arm_systick_isr() {
	display.strobeNextRow(); 

}

extern "C" void arm_gpiote_isr() {
	buttonSource.handleInterrupt(); 
}

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

