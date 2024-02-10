#import "SysTick.h"
#import "ImageMatrix.h"

class LEDDisplay {
	private: 
		LEDDisplay(); 
		
		int currentRow = 0;
		int row_bits[5] = {21, 22, 15, 24, 19};

		ImageMatrix matrix;
	public: 
        static LEDDisplay& getInstance();

		int columnOffset = 0; 
		
		void display(ImageMatrix matrix); 
		
		
		void strobeNextRow();
		
		void enable();
		void disable();
};

