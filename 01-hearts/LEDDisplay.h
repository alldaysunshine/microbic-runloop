#import "SysTick.h"

class LEDDisplay {
	private: 
		
		int currentRow = 0;
		
		int row_bits[5] = {21, 22, 15, 24, 19};
		
		int matrix[5][5];
		
		SysTick* systick;
	public: 
    	LEDDisplay(SysTick& systick);
		
		void set(int (*array)[5][5]); 
		
		
		void strobeNextRow();
		
		void enable();
		void disable();
};

