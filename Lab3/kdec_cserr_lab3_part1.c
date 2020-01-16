/*	Partner(s) Name & E-mail: Kristian De Castro kdec001@ucr.edu 
 *	Christopher Serrano cserr011@ucr.edu
 *	Lab Section: 024
 *	Assignment: Lab 3  Exercise 1 
 *	
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>


// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as outputs,
	DDRC = 0xFF; PORTC = 0x00;
	// initialize to 0s
	//unsigned char tmpB = 0x00; // intermediate variable used for port updates
	
	while(1)
	{
		unsigned char count = 0x00;
		// 1) Read Inputs and assign to variables
		for(unsigned char i = 0; i < 8; i++){
			if(GetBit(PINA, i)){
				count++;
			}
			if(GetBit(PINB, i)){
				count++;
			}
		}
		// 3) write results to port
		PORTC = count;
	}
	return 0;
}

