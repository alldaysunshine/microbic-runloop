#import "Observer.h"
#import "UART.h"

extern UART uart; 

Observer::Observer(std::function<void(Event*)> c) {
	callback = c; 
}

void Observer::notify(Event* event) {
	callback(event);
	uart.transmitString("got notification\r\n");

}
