#import "AsmBridge.h"
#import "Button.h"

#define GPIOTE_BASE 0x40006000
#define GPIOTE_IN0  0x40006100
#define GPIOTE_INTENSET0 0x40006304
#define GPIOTE_INTENCLR0 0x40006308
#define GPIOTE_CONFIG0 0x40006510
#define GPIOTE_CONFIG1 0x40006514

#define BUTTON_A_PIN 14
#define BUTTON_B_PIN 23

Button::Button(ButtonLocation _location) {
	location = _location; 
}

void Button::enable() {
	if (location == ButtonA) {
		PUT32(GPIO_DIRCLR0, (1 << BUTTON_A_PIN)); // Configure button as input
	
		PUT32(GPIO_CNF0 + 4 * BUTTON_A_PIN, 
			0 << 0 |
			1 << 1 |
			0 << 2 |
			0 << 8 |
			0 << 16
			);
			
		PUT32(GPIOTE_CONFIG0,
			1 << 0 |
			BUTTON_A_PIN << 8 |
			2 << 16
		); 
	} else {
		PUT32(GPIO_DIRCLR0, (1 << BUTTON_B_PIN)); // Configure button as input
	
		PUT32(GPIO_CNF0 + 4 * BUTTON_B_PIN, 
			0 << 0 |
			1 << 1 |
			0 << 2 |
			0 << 8 |
			0 << 16
			);
			
		PUT32(GPIOTE_CONFIG1,
			1 << 0 |
			BUTTON_B_PIN << 8 |
			2 << 16
		); 
	}
}

void Button::clear() {
	PUT32(GPIOTE_IN0, 0);
}


bool Button::state() {
	unsigned int device_pin = (location == ButtonA ? (1 << BUTTON_A_PIN) : (1 << BUTTON_B_PIN)); 

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

