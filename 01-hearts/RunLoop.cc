#include "AsmBridge.h"
#include "RunLoop.h"
#include "Event.h"
#include "Timer.h"

RunLoop::RunLoop() {
	
}

RunLoop& RunLoop::getMain()
{
	static RunLoop instance; // Guaranteed to be destroyed.
						  // Instantiated on first use.
	return instance;
}


void RunLoop::run() {
	Timer timer; 	
	timer.enable(); 
	
	while (1) {
		unsigned int t = timer.value(); 
		
		runloopTime = t; 

		processScheduledBlocks(); 
		processNextEvent(); 
				
		// TODO: Improve with timer
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
	
	scheduledBlocks.push(block);
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
	while(!scheduledBlocks.empty() && runloopTime > scheduledBlocks.top()->runAfter) {
		scheduledBlocks.top()->callback(); 
		delete scheduledBlocks.top(); 
		scheduledBlocks.pop(); 
    }
}

