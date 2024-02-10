#import "AsmBridge.h"
#import "Button.h"

#define GPIOTE_BASE 0x40006000
#define GPIOTE_IN0  0x40006100
#define GPIOTE_INTENSET0 0x40006304
#define GPIOTE_INTENCLR0 0x40006308
#define GPIOTE_CONFIG0 0x40006510
#define GPIOTE_CONFIG1 0x40006514

struct ButtonConfiguration buttonA(14, 0);
struct ButtonConfiguration buttonB(23, 1);


Button::Button(ButtonConfiguration& _configuration) : configuration(_configuration) {
}


void Button::enable() {
		PUT32(GPIO_DIRCLR0, (1 << configuration.pin)); // Configure button as input
	
		PUT32(GPIO_CNF0 + 4 * configuration.pin, 
			0 << 0 |
			1 << 1 |
			0 << 2 |
			0 << 8 |
			0 << 16
			);
			
		PUT32(GPIOTE_CONFIG0 + 4 * configuration.gpiote_event_in,
			1 << 0 |
			configuration.pin << 8 |
			2 << 16
		); 
}


bool Button::state() {
	unsigned int device_pin = (1 << configuration.pin);
	
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

