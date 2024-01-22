#import "AsmBridge.h"
#import "LEDDisplay.h"


#define LED_MASK0 0xd1688800
#define LED_MASK1 0x00000020


LEDDisplay::LEDDisplay(SysTick& systick) {
	this->systick = &systick; 
}


void LEDDisplay::set(int (*array)[5][5]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			matrix[i][j] = (*array)[i][j];
		}
	}
}

void LEDDisplay::strobeNextRow() {
	  PUT32(GPIO_OUTCLR0, LED_MASK0);
	  PUT32(GPIO_OUTCLR1, LED_MASK1);

	  PUT32(GPIO_OUTSET0, (1 << row_bits[currentRow]) | 
	  	(!matrix[currentRow][0] << 28) | 
	  	(!matrix[currentRow][1] << 11) | 
	  	(!matrix[currentRow][2] << 31) | 
	  	(!matrix[currentRow][4] << 30));
	  PUT32(GPIO_OUTSET1, (!matrix[currentRow][3] << 5));
	  
	  currentRow = (currentRow + 1) % 5;
}


void LEDDisplay::enable() {
	PUT32(GPIO_DIRSET0, LED_MASK0);
	PUT32(GPIO_DIRSET1, LED_MASK1);
}

void LEDDisplay::disable() {
}

