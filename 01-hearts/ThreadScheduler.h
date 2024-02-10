#include <vector>
#include "Thread.h"

class ThreadScheduler {
	private: 
    	ThreadScheduler();
    	
    	std::vector<Thread> threads; 
       	std::vector<Thread>::iterator currentThread; 
	public: 
        static ThreadScheduler& getInstance();

		void enable();
		void disable(); 
		
		void yield(); 

		void switchContext(); 
	//	void createThread(std::function<void>(void)function); 
};

