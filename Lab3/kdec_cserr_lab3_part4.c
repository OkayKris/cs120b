/*	Partner(s) Name & E-mail: Kristian De Castro kdec001@ucr.edu
 *	Christopher Serrano cserr011@ucr.edu
 *	Lab Section: 024
 *	Assignment: Lab 3  Exercise 4
 *
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;

	unsigned char tempB = 0x00;
	unsigned char tempC = 0x00;
	while(1)
	{
		tempB = (PINA & 0xF0) >> 4; // 1111 0000 of PINA to 0000 1111 of PORTB
		tempC = (PINA & 0x0F) << 4; // same kinda thing for this one

		PORTB = tempB;
		PORTC = tempC;
	}
	return 0;
}
