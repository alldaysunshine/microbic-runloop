#import "Event.h"

class Source {
	private: 
		
	public: 
		virtual bool ready();	
		
		virtual Event* consumeEvent(); 
		virtual ~Source() {}
};

