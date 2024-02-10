#import "AsmBridge.h"
#import "Timer.h"

Timer::Timer() {
	
}

void Timer::enable() {
	// Set timer mode
	PUT32(0x40008000 + 0x504, 0); 

	// Set bitmode 
	PUT32(0x40008000 + 0x508, 3); 

	// Set prescaler (2^24 / 2^PRESCALE), 1000 Tocks per Secondd
	PUT32(0x40008000 + 0x510, 9); 
	// Timer 0 Start
	PUT32(0x40008000 + 0x000, 1); 
}

unsigned int Timer::value() {
	 // Capture value to CC
	 PUT32(0x40008000 + 0x040, 1);
	 
	 // Get value from CC, generate 1000 Ticks per second
	 return GET32(0x40008000 + 0x540) >> 5; 
}

void Timer::disable() {
	PUT32(0x40008000 + 0x004, 1); 
}

