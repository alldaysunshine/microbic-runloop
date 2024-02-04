
#import <vector>
#include <map>

class ImageMatrix {

	public: 
		std::vector<unsigned char> matrix; 

		unsigned int columns; 
		unsigned int rows; 
		
		unsigned int bytesPerRow; 
		
		ImageMatrix(); 
		ImageMatrix(unsigned int _columns, unsigned int _rows, std::vector <unsigned char> _matrix); 
		
		ImageMatrix(unsigned char character); 

		ImageMatrix(std::string str); 

		const static unsigned char font[475];
};