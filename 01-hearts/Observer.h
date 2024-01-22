#import "Event.h"

class Observer {
	private: 
		
	public: 
		virtual void notify(Event* event);
		virtual ~Observer() {}
};