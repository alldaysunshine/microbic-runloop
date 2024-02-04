#import "Observer.h"
#import "UART.h"

extern UART uart; 

Observer::Observer(unsigned int _event_mask, std::function<void(Event*)> c) {
	event_mask = _event_mask;
	callback = c; 
}

void Observer::notify(Event* event) {
	callback(event);
	uart.transmitString("got notification\r\n");

}
