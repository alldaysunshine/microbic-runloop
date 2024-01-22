#import <vector>
#import <queue>
#import "Source.h"
#import "Observer.h"





class RunLoop {
	private: 
		std::vector<Source*> sources;
		std::vector<Observer*> observers;
		
		unsigned int eventCounter = 0; 
		
	public: 
    	RunLoop();

		void addSource(Source& source);
		void addObserver(Observer& observer);
    	
		void processNextEvent();

		void run();
};

