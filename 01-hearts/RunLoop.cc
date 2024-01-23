#include "AsmBridge.h"
#include "RunLoop.h"
#include "UART.h"
#include "Source.h"
#include "Observer.h"
#include "Event.h"
#include "Timer.h"

RunLoop::RunLoop() {
	
}

extern UART uart; 


void RunLoop::run() {
	// RunLoop
	int i = 0; 
	
	Timer timer; 	
	timer.enable(); 
	
	while (1) {
	unsigned int t = timer.value(); 
		runloopTime = t; 

		processScheduledBlocks(); 
		processNextEvent(); 
		

		delay(100000);
	}
	timer.disable(); 
}


void RunLoop::addObserver(Observer &observer) {
	observers.push_back(&observer);
}


void RunLoop::addSource(Source& source) {
	sources.push_back(&source);
}

void RunLoop::runAfter(unsigned int delay, std::function<void()> function) {
	ScheduledBlock block; 
	
	block.runAfter = runloopTime + delay; 
	block.callback = function; 
	
	scheduledBlocks.push_back(block);
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

void RunLoop::processScheduledBlocks() {
	auto it = scheduledBlocks.begin(); 
	
	while(it != scheduledBlocks.end()) {
		if (runloopTime > it->runAfter) {
			it->callback();
	        it = scheduledBlocks.erase(it);
		} else {
			++it; 
		}
    }
}

