#include "AsmBridge.h"
#include "RunLoop.h"
#include "Event.h"
#include "Timer.h"

RunLoop::RunLoop() {
	
}

void RunLoop::run() {
	Timer timer; 	
	timer.enable(); 
	
	scheduledBlocks.reserve(100);

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
	ScheduledBlock *block = new ScheduledBlock; 
	
	block->runAfter = runloopTime + delay; 
	block->callback = function; 
	
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
			if ((*it)->event_mask & event->event_id) {
				(*it)->notify(event);
			}
		}
		delete event;
	}
}


void RunLoop::processScheduledBlocks() {
	auto it = scheduledBlocks.begin(); 
	
	while(it != scheduledBlocks.end()) {
		if (runloopTime > (*it)->runAfter) {
			(*it)->callback();
			delete (*it);

	        it = scheduledBlocks.erase(it);
		} else {
			++it; 
		}
    }
}

