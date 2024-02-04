#import "Event.h"
#import <functional>

class Observer {
	private: 
		std::function<void(Event*)> callback;
	public: 
		unsigned int event_mask = 0; 

		Observer(unsigned int _event_mask, std::function<void(Event*)> c);

		virtual void notify(Event* event);
		
		virtual ~Observer() {}
};