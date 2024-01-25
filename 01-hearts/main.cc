
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


ImageMatrix bigHeartMatrix(5, 5); 

ImageMatrix smallHeartMatrix(5, 5); 

ImageMatrix arrowLeft(24, 5); 

SysTick systick; 

LEDDisplay display(systick); 
UART uart; 

Button button; 

static RunLoop runloop; 

ButtonSource buttonSource(button); 

static bool animationRunning = true; 

Observer observer([](Event * event) {
animationRunning = false; 
	display.columnOffset = 0; 
			if (event->state == 1) {
				runloop.runAfter(0, []() {
					display.display(bigHeartMatrix);
				});
				runloop.runAfter(500, []() {
					display.display(smallHeartMatrix);
				});
				runloop.runAfter(1000, []() {
					display.display(bigHeartMatrix);
				});
				runloop.runAfter(1500, []() {
					display.display(smallHeartMatrix);
				});
				runloop.runAfter(2000, []() {
					animationRunning = true; 
					display.display(arrowLeft);
				});
			} 
}); 

static std::function<void(void)> animationCallback; 

extern "C" void arm_systick_isr() {
	display.strobeNextRow(); 

}

extern "C" void arm_gpiote_isr() {
	buttonSource.handleInterrupt(); 
}


int main(void) {
	bigHeartMatrix.matrix.push_back(0b01010); 
	bigHeartMatrix.matrix.push_back(0b11111); 
	bigHeartMatrix.matrix.push_back(0b11111); 
	bigHeartMatrix.matrix.push_back(0b01110); 
	bigHeartMatrix.matrix.push_back(0b00100); 

	smallHeartMatrix.matrix.push_back(0b100000); 
	smallHeartMatrix.matrix.push_back(0b101010); 
	smallHeartMatrix.matrix.push_back(0b101110); 
	smallHeartMatrix.matrix.push_back(0b100100); 
	smallHeartMatrix.matrix.push_back(0b100000); 

	arrowLeft.matrix.push_back(0b00100); 
	arrowLeft.matrix.push_back(0b00100); 
	arrowLeft.matrix.push_back(0b00100); 

	arrowLeft.matrix.push_back(0b01000); 
	arrowLeft.matrix.push_back(0b01000); 
	arrowLeft.matrix.push_back(0b01000); 

	arrowLeft.matrix.push_back(0b10000); 
	arrowLeft.matrix.push_back(0b10000); 
	arrowLeft.matrix.push_back(0b10000); 

	arrowLeft.matrix.push_back(0b01000); 
	arrowLeft.matrix.push_back(0b01000); 
	arrowLeft.matrix.push_back(0b01000); 

	arrowLeft.matrix.push_back(0b00100); 
	arrowLeft.matrix.push_back(0b00100); 
	arrowLeft.matrix.push_back(0b00100); 

	display.display(arrowLeft);

	display.enable(); 

	systick.enable();
	uart.enable(); 

	button.enable(); 

	buttonSource.enableInterrupt(); 
	
	runloop.addObserver(observer);
	runloop.addSource(buttonSource);
	
	int animationCounter = 23; 
	
	animationCallback = [&animationCounter]{
		if (animationRunning) {
		display.columnOffset = animationCounter;
		animationCounter--;
		if (animationCounter < 0) {
			animationCounter = 23; 
		}
		}
		runloop.runAfter(200, animationCallback);
	};
	runloop.runAfter(200, animationCallback);

	
	runloop.run(); 
	 
  	return 0;
}

