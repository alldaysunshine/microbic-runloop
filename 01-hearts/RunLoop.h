#import <vector>
#import <queue>
#import "Source.h"
#import "Observer.h"
#import "ScheduledBlock.h"



class RunLoop {
	private: 
		std::vector<Source*> sources;
		std::vector<Observer*> observers;
		
		std::vector<ScheduledBlock> scheduledBlocks;
		
		unsigned int eventCounter = 0; 
		unsigned int runloopTime = 0; 
		
	public: 
    	RunLoop();

		void addSource(Source& source);
		void addObserver(Observer& observer);
		
		void runAfter(unsigned int delay, std::function<void()> function);
    	
		void processNextEvent();
		void processScheduledBlocks();

		void run();
};

