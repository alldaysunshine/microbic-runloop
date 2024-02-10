#import <functional>


class ScheduledBlock {
	public: 
		unsigned int runAfter; 
	 	std::function<void()> callback;
};

struct CmpScheduledBlockPtrs
{
    bool operator()(const ScheduledBlock* lhs, const ScheduledBlock* rhs) const
    {
        return lhs->runAfter > rhs->runAfter;
    }
};
