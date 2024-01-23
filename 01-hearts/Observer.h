#import "Event.h"
#import <functional>

class Observer {
	private: 
		std::function<void(Event*)> callback;
	public: 
		Observer(std::function<void(Event*)> c);

		virtual void notify(Event* event);
		
		virtual ~Observer() {}
};