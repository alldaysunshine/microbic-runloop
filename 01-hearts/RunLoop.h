#import <vector>
#import <queue>
#import "Source.h"
#import "Observer.h"
#import "ScheduledBlock.h"
#include <queue>
#include <list>


class RunLoop {
   private:
    	RunLoop();

		std::vector<Source*> sources;
		std::vector<Observer*> observers;
		
		std::priority_queue<ScheduledBlock*,std::vector<ScheduledBlock*>,CmpScheduledBlockPtrs> scheduledBlocks;
		
		unsigned int runloopTime = 0; 
	public: 
        static RunLoop& getMain();

		void addSource(Source& source);
		void addObserver(Observer& observer);
		
		void runAfter(unsigned int delay, std::function<void()> function);
    	
		void processNextEvent();
		void processScheduledBlocks();

		void run();
};

