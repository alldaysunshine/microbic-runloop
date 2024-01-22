
class Button {
	private: 
		unsigned int counter = 0; 
		
	public: 
    	Button();

		void enable();
		void disable(); 
		
		bool state();
		void clear();
};

