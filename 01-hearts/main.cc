#import "AsmBridge.h"

#import <iostream>
#import <string>

#import "LEDDisplay.h"
#import "SysTick.h"
#import "UART.h"
#import "Button.h"

#import "ButtonSource.h"
#import "ImageMatrix.h"

#import "RunLoop.h"


ImageMatrix startMatrix("Welcome >>> Press button >>>");

ImageMatrix bigHeartMatrix(5, 5, {
	0b01010000, 
	0b11111000,
	0b11111000,
	0b01110000,
	0b00100000
}); 

ImageMatrix smallHeartMatrix(5, 5, { 
	0b00000000, 
	0b01010000,
	0b01110000,
	0b00100000,
	0b00000000
}); 


SysTick systick; 

LEDDisplay display(systick); 
UART uart; 

Button button(ButtonB); 

RunLoop runloop; 

ButtonSource buttonSource(button); 

bool animationRunning = true; 

int animationCounter = 0; 

std::function<void(void)> animationCallback; 
	
Observer observer(BUTTON_EVENT, [](Event * event) {
	if (event->state == 1) {
		animationRunning = false; 
		animationCounter = 0; 
		display.columnOffset = 0; 
		display.display(smallHeartMatrix);
		
		runloop.runAfter(400, []() {
			display.display(bigHeartMatrix);
		});
		runloop.runAfter(800, []() {
			display.display(smallHeartMatrix);
		});
		runloop.runAfter(1000, []() {
			display.display(bigHeartMatrix);
		});
		runloop.runAfter(1200, []() {
			display.display(smallHeartMatrix);
		});
		runloop.runAfter(1600, []() {
			display.display(bigHeartMatrix);
		});
		runloop.runAfter(2000, []() {
			animationRunning = true; 
			animationCounter = 0; 
			display.display(startMatrix);
		}); 
	} 
}); 

extern "C" void arm_systick_isr() {
	display.strobeNextRow(); 
}

extern "C" void arm_gpiote_isr() {
	 buttonSource.handleInterrupt(); 
}

int main(void) {
	display.display(startMatrix);

	display.enable(); 
	systick.enable();

	uart.enable(); 

	button.enable(); 

	buttonSource.enableInterrupt(); 
	
	runloop.addObserver(observer);
	runloop.addSource(buttonSource);
	
	animationCallback = [](void) {
		if (animationRunning) {
			animationCounter = (animationCounter + 1) % startMatrix.columns; 
			display.columnOffset = animationCounter;
		}
		runloop.runAfter(100, animationCallback);
	}; 

	runloop.runAfter(100, animationCallback);

	runloop.run(); 
	
  	return 0;
}

