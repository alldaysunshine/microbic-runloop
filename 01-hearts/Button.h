
enum ButtonLocation {
	ButtonA, 
	ButtonB
};

struct ButtonConfiguration {
	unsigned int pin; 
	
	unsigned int gpiote_event_in; 
	
	ButtonConfiguration(unsigned int _p, unsigned int _g) 
		: pin(_p), gpiote_event_in(_g) {};
};

extern ButtonConfiguration buttonA; 
extern ButtonConfiguration buttonB; 

class Button {
	private: 
				
	public: 
		ButtonLocation location; 
		ButtonConfiguration& configuration; 

    	Button(ButtonConfiguration& _configuration);

		void enable();
		void disable(); 
		
		bool state();
		
		void clear();
};

