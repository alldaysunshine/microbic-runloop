#include "AsmBridge.h"
#include "RunLoop.h"
#include "UART.h"
#include "Source.h"
#include "Observer.h"
#include "Event.h"

RunLoop::RunLoop() {
	
}

extern UART uart; 


void RunLoop::run() {
	// RunLoop
	int i = 0; 
	
	while (1) {
		processNextEvent(); 
		delay(100000);
	}
}

void RunLoop::addObserver(Observer &observer) {
	observers.push_back(&observer);
}

void RunLoop::addSource(Source& source) {
	sources.push_back(&source);
}

void RunLoop::processNextEvent() {
	Event* event; 
	bool ready = false; 
	
	for (auto it = sources.begin(); it != sources.end(); ++it) {
		if ((*it)->ready()) {
			event = (*it)->consumeEvent();
			ready = true; 
			break; 
		}
	}
	if (ready) {
		for (auto it = observers.begin(); it != observers.end(); ++it) {
			(*it)->notify(event);
		}
	delete event;
	}
}

