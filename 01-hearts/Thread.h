
class Thread {
	public: 
    	Thread();
    	
    	unsigned long long wakeup_timestamp;
    	int *stack;
    	int *stackPointer;
    	unsigned short int stacksize;
  //  	enum threadState state;
    	unsigned char threadID;

};

