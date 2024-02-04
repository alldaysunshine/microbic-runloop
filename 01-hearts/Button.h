
enum ButtonLocation {
	ButtonA, 
	ButtonB
};


class Button {
	private: 
				
	public: 
		ButtonLocation location; 

    	Button(ButtonLocation _location);

		void enable();
		void disable(); 
		
		bool state();
		
		void clear();
};

