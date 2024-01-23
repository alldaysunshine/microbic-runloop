
class ScheduledBlock {
	public: 
		unsigned int runAfter; 
		unsigned int executeAfter; 
		
	 	std::function<void()> callback;
};

