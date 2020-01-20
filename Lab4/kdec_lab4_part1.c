/*	Partner(s) Name & E-mail: Kristian De Castro kdec001@ucr.edu
 *	Lab Section: 024
 *	Assignment: Lab 4  Exercise 1
 *
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

enum bStates{Start, offR, onP, onR, offP} state;

void TickButton(){
	switch(state){
		case Start:
			PORTB = 0x01;
			state = offR;
			break;
		case offR:
			if(PINA == 0x01){
				state = onP;
			} else {
				state = offR;
			}
			break;
		case onP:
			if(PINA == 0x01){
				state = onP;
			} else {
				state = onR;
			}
			break;
		case onR:
			if(PINA == 0x01){
				state = offP;
			} else {
				state = onR;
			}
			break;
		case offP:
			if(PINA == 0x01){
				state = offP;
			} else {
				state = offR;
			}
			break;

		default:
			break;
	}

	switch(state){
		case Start:
			break;

		case offR:
			PORTB = 0x02;
			break;
		case onP:
			PORTB = 0x01;
			break;
		case onR:
			break;
		case offP:
			PORTB = 0x02;
			break;
		default:
			break;
	}

}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x01;
	state = Start;
    while (1)
    {
		TickButton();
    }
}
