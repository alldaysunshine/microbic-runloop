#include "AsmBridge.h"
#include "UART.h"

void UART::enable() {
	PUT32(0x40002500, 0); // Disable UART
	
	PUT32(0x40002524,    0x00275000); // Set Baudrate to 115200
	
	PUT32(0x4000256c, 0); // No flow control, no parity
	PUT32(0x4000250c, 6); // Select USB
	PUT32(0x40002514, 6); // Select USB
	
	PUT32(0x40002500, 4); // Enable UART

	PUT32(0x40002008, 1); // Start Transmitter

	PUT32(0x40002144, 0); // RXReady = 0
}

void UART::transmitByte(char ch) {
	PUT32(0x4000211c, 0);
	PUT32(0x4000251c, ch);
	while (!GET32(0x4000211c)) {}
}

void UART::transmitString(std::string str) {
	for(std::string::iterator it = str.begin(); it != str.end(); ++it) {
    	transmitByte(*it);
	}
}
