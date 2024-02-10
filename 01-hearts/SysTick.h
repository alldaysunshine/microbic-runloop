
class SysTick {
	private: 
    	SysTick();

	public: 
        static SysTick& getInstance();

		void enable();
		void disable(); 
};

