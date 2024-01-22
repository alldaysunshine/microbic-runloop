#import "Observer.h"
#import "LEDDisplay.h"
#import "UART.h"

class ButtonObserver : public Observer {
	private: 
		LEDDisplay* display; 
		UART* uart; 

	public: 
		ButtonObserver(LEDDisplay& d, UART& u);
		virtual void notify(Event* event) override;

};