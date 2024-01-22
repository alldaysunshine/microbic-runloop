#import "ButtonObserver.h"

#define GPIOTE_IN0  0x40006100
#define GPIOTE_IN1  0x40006104

ButtonObserver::ButtonObserver(LEDDisplay& d, UART& u) {
	display = &d; 
	uart = &u; 
}

void ButtonObserver::notify(Event* event) {
	int m[5][5] = {
		{ 0, 1, 0, 1, 0},
		{ 1, 1, 1, 1, 1},
		{ 1, 1, 1, 1, 1},
		{ 0, 1, 1, 1, 0},
		{ 0, 0, 1, 0, 0}
	};
	
	int n[5][5] = {
		{ 0, 0, 0, 0, 0},
		{ 0, 1, 0, 1, },
		{ 0, 1, 1, 1, 0},
		{ 0, 0, 1, 0, 0},
		{ 0, 0, 0, 0, 0}
	};
	
			if (event->state == 1) {
				display->set(&m);
			} else {
				display->set(&n);
			}
//	uart->transmitString("Button A: ");
	if (event->state == 1) {
	//	uart->transmitString("Pressed\r\n");
	} else {
	//	uart->transmitString("Released\r\n");
	}

}
