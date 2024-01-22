#import "Source.h"
#import "Button.h"

#import <queue>

class ButtonSource : public Source {
	private: 
		ButtonSource(const ButtonSource&) = delete;

		Button* button; 
		std::queue<Event*> eventQueue; 
		
		int trackedState = 0; 
	public: 
		ButtonSource(Button& button);

		virtual bool ready();	

		virtual Event* consumeEvent(); 
		void addEvent(Event* event); 
		
		void updateState(); 

		void enableInterrupt(); 
		void handleInterrupt(); 
		void disableInterrupt(); 

		void handlePolling(); 

};
