#include <string>

class UART {
	private: 
		
	public: 
		void enable();
		void disable();
		void transmitByte(char ch);
		void transmitString(std::string str);


};

