#import "AsmBridge.h"

#import "ButtonSource.h"

#define GPIOTE_INTENSET0 0x40006304
#define GPIOTE_INTENCLR0 0x40006308

#define GPIOTE_IN0  0x40006100


ButtonSource::ButtonSource(Button& _button) : button(_button) {
}

bool ButtonSource::ready() {
	if (trackedState == 1) {
		if (button.state() == 0) {
			trackedState = 0; 
	
			Event* event = new Event(); 
			event->event_id = BUTTON_EVENT; 
			event->state = 0; 
			eventQueue.push(event);
		}
	}
	return !eventQueue.empty(); 
}

Event* ButtonSource::consumeEvent() {
	Event* ev = eventQueue.front(); 
	eventQueue.pop();
	return ev;
}


void ButtonSource::enableInterrupt() {
	PUT32(GPIOTE_INTENSET0, 1 << button.configuration.gpiote_event_in); 
	PUT32(0xE000E100, (1 << 6));
}

/*
 * We only catch button down interrupts, because interrupt is duplicated.
 * Button Up is performed on the RunLoop. 
 *
 * It might be we miss some button up events, but we make sure that we 
 * catch all button down (for games etc.).
 *
 * Essentially, we start tracking of button press duration and button up
 * via the RunLoop as soon as we get an interrupt from a button down event.
 */
void ButtonSource::handleInterrupt() {
	unsigned int r = (unsigned int)GPIOTE_IN0 + 4 * button.configuration.gpiote_event_in; // button.configuration.gpiote_event_in == 1 ? GPIOTE_IN0 : GPIOTE_IN1; 
	unsigned int downState = GET32(r);

	if (downState) {
		// Add button up first
		if (trackedState == 1) {
			Event* eventUp = new Event(); 
			eventUp->event_id = BUTTON_EVENT; 
			eventUp->state = 0; 
			eventQueue.push(eventUp);
		
			Event* eventDown = new Event(); 
			eventDown->event_id = BUTTON_EVENT; 
			eventDown->state = 1; 
			eventQueue.push(eventDown);
		} else {
			Event* event = new Event(); 
			event->event_id = BUTTON_EVENT; 
			event->state = 1; 
			eventQueue.push(event);
		
			trackedState = 1; 
		}
	}
	
	PUT32(r, 0);
}

void ButtonSource::disableInterrupt() {
	PUT32(GPIOTE_INTENCLR0, 0b11); 
	PUT32(0xE000E100, (1 << 6));
}

