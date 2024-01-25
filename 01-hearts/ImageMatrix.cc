#import "ImageMatrix.h"

#define BITS_PER_PIXEL 1

/*
 * Colums are rounded to a multiple of a byte
 */
 

ImageMatrix::ImageMatrix(unsigned int _columns, unsigned int _rows) {
	columns = _columns; 
	rows = _rows; 
	
	bytesPerRow = BITS_PER_PIXEL * ((columns + 8 - 1) / 8);
}

ImageMatrix::ImageMatrix() {
	columns = 5; 
	rows = 5; 
	
	bytesPerRow = 1; 
	
	matrix.push_back(0b10101);
	matrix.push_back(0b10101);
	matrix.push_back(0b10101);
	matrix.push_back(0b10101);
	matrix.push_back(0b10101);
}