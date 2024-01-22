#import "Observer.h"
#import "UART.h"

extern UART uart; 

void Observer::notify(Event* event) {
	uart.transmitString("got notification\r\n");

}
