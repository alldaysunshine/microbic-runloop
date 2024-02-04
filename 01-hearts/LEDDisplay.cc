#import "AsmBridge.h"
#import "LEDDisplay.h"


#define LED_MASK0 0xd1688800
#define LED_MASK1 0x00000020

#define CHECK_BIT(var, pos) ((var) & (1<<(pos)))

#define GET_BYTE(m, row, col) m.matrix.at((row * m.bytesPerRow + ((col) / 8)))

#define GET_BIT(m, row, col) \
	(((col + columnOffset) > m.columns - 1 || (col + columnOffset) < 0) ? 0 : \
		CHECK_BIT(GET_BYTE(matrix, currentRow, col + columnOffset), 7 - (col + columnOffset) % 8) \
	 )
	


LEDDisplay::LEDDisplay(SysTick& systick) {
	this->systick = &systick; 
}

void LEDDisplay::display(ImageMatrix _m) {
	matrix = _m; 
}

void LEDDisplay::strobeNextRow() {
	PUT32(GPIO_OUTCLR0, LED_MASK0);
 	PUT32(GPIO_OUTCLR1, LED_MASK1);
	
	PUT32(GPIO_OUTSET1, (!GET_BIT(matrix, currentRow, 3) << 5));
	PUT32(GPIO_OUTSET0, (1 << row_bits[currentRow]) | 
	  	(!GET_BIT(matrix, currentRow, 0) << 28) | 
	  	(!GET_BIT(matrix, currentRow, 1) << 11) | 
	  	(!GET_BIT(matrix, currentRow, 2) << 31) | 
	  	(!GET_BIT(matrix, currentRow, 4) << 30));
	  
	currentRow = (currentRow + 1) % 5;
}


void LEDDisplay::enable() {
	PUT32(GPIO_DIRSET0, LED_MASK0);
	PUT32(GPIO_DIRSET1, LED_MASK1);
	
	//    SET_FIELD(_GPIO_PINCNF(pin), GPIO_PINCNF_DRIVE, mode);

}

void LEDDisplay::disable() {
}

