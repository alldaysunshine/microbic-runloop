#import "AsmBridge.h"
#import "Button.h"

#define GPIOTE_BASE 0x40006000
#define GPIOTE_IN0  0x40006100
#define GPIOTE_INTENSET0 0x40006304
#define GPIOTE_INTENCLR0 0x40006308
#define GPIOTE_CONFIG0 0x40006510
#define GPIOTE_CONFIG1 0x40006514


Button::Button( ) {
	
}

void Button::enable() {
	unsigned int device_pin = (1 << 14); // Button 1; 
	
	PUT32(GPIO_DIRCLR0, device_pin); // Configure button as input
	
	PUT32(GPIO_CNF0 + 4 * 14, 
		0 << 0 |
		1 << 1 |
		0 << 2 |
		0 << 8 |
		0 << 16
		);
	
	PUT32(GPIOTE_CONFIG0,
		1 << 0 |
		14 << 8 |
		2 << 16
	); 
}

void Button::clear() {
	PUT32(GPIOTE_IN0, 0);
}


bool Button::state() {
	unsigned int device_pin = (1 << 14); // Button 1; 

	unsigned int state = GET32(GPIO_IN0);
	
	unsigned int checked = state & device_pin;

	if (checked != 0) {
		return 0; 
	} else {
		return 1; 
	}
}


void Button::disable() {

}

