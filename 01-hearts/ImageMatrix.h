
#import <vector>

class ImageMatrix {

	public: 
		std::vector<unsigned char> matrix; 

		unsigned int columns; 
		unsigned int rows; 
		
		unsigned int bytesPerRow; 
		
		ImageMatrix(); 
		ImageMatrix(unsigned int _columns, unsigned int _rows); 
};