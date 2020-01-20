/*	Partner(s) Name & E-mail: Kristian De Castro kdec001@ucr.edu
 *	Christopher Serrano cserr011@ucr.edu
 *	Lab Section: 024
 *	Assignment: Lab 3  Exercise 3
 *
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs,

	while(1){
		unsigned char fuel = PINA & 0x0F;
		unsigned char light = 0x00;
		unsigned char lowFuel = 0x00;
		unsigned char key = PINA & 0x10;
		unsigned char seated = PINA & 0x20;
		unsigned char seatbelt = PINA & 0x40;
		if(fuel == 0){
			lowFuel = 0x40;
		}
		if(fuel == 1 || fuel == 2){
			light = 0x20;
			lowFuel = 0x40;
		}
		if (fuel == 3 || fuel == 4){
			light = 0x30;
			lowFuel = 0x40;
		}
		if(fuel == 5 || fuel == 6){
			light = 0x38;
		}
		if (fuel == 7 || fuel == 8 || fuel == 9) {
			light = 0x3C;
		}
		if (fuel == 10 || fuel == 11 || fuel == 12) {
			light = 0x3E;
		}
		if (fuel == 13 || fuel == 14 || fuel == 15) {
			light = 0x3F;
		}
		if(key == 0x10 && seated == 0x20 && seatbelt == 0){
			light = light | 0x80;
		}
		PORTC = light | lowFuel;
	}


	return 0;
}
