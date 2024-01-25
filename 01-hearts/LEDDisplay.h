#import "SysTick.h"
#import "ImageMatrix.h"

class LEDDisplay {
	private: 
		
		int currentRow = 0;
		int row_bits[5] = {21, 22, 15, 24, 19};

				
		ImageMatrix matrix;
		
		SysTick* systick;
	public: 
		int columnOffset = 0; 

    	LEDDisplay(SysTick& systick);
		
		void display(ImageMatrix matrix); 
		
		
		void strobeNextRow();
		
		void enable();
		void disable();
};

