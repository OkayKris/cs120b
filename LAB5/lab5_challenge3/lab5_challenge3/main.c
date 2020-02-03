/*    Partner(s) Name & E-mail: Kristian De Castro kdec001@ucr.edu
 *    Lab Section: 024
 *    Assignment: Lab 5  Challenge 3
 *
 *
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */ 

#define F_CPU 10000000UL
#include <avr/io.h>
#include <avr/delay.h>


enum festiveState{start, wait, inc, waitoff}state;
unsigned char check = 0x00;
void lightTick(){

	unsigned char button = ~PINA & 0x01;
	switch(state){
		case start:
		state = wait;
		break;

		case wait:
		if(button == 0x01){
			state = inc;
		} else {
			state = wait;
		}
		break;
		
		case inc:
		state = waitoff;
		_delay_ms(175);
		break;
	
		case waitoff:
		if(button == 0x01){
			state = waitoff;
		} else {
			state = wait;
		}
		
		default:
		state = wait;
		break;

	}

	switch(state){
		case start:
		PORTB = 0x00;
		check = 0;
		break;
		
		case wait:
		break;
		
		case inc:
		if(check == 0){
			PORTB = 0x3F;	//11 1111
		} else if (check == 1){
			PORTB = 0x2A;	//10 1010
		} else if (check == 2){
			PORTB = 0x15;	//01 0101
		} else if (check == 3){
			PORTB = 0x03;	//00 0111
		} else if (check == 4){
			PORTB = 0x30;	//11 1000
		} else if (check == 5){
			PORTB = 0x21;	//10 0001
		} else if (check == 6){
			PORTB = 0x0C;	//00 1100
		} else if (check == 7){
			PORTB = 0x1E;	//01 1110
		}
		
		check = check + 1;
		if(check == 8){
			check = 0;
		}
		break;
		
		case waitoff:
		break;
		
		default:
		break;
		
	}
}

int main(void)
{

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	state = start;
	while (1)
	{
		lightTick();
	}

}
