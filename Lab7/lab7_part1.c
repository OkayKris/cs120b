/*	Partner(s) Name & E-mail: Kristian De Castro kdec001@ucr.edu
 * Raoul Larios, Grant Beatty
 *	Lab Section: 024
 *	Assignment: Lab 7  Exercise 1
 *
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#include "io.c"

enum states{Start, wait, inc, dec, res, waitoff} state;

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimeISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0)
	{
		TimeISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

//unsigned char lcd_number = 0x00;
unsigned char tempC = 0x00;

void tickButton(){
	unsigned char input = (~PINA) & 0x03;
	

	switch(state){
		case Start:
		state = wait;
		tempC = 0x00;
		break;

		case wait:
		if(input == 0x01){
			state = inc;
			} else if(input == 0x02){
			state = dec;
			} else if(input == 0x03){
			state = res;
			} else {
			state = wait;
		}
		break;

		case inc:
		state = waitoff;
		break;

		case dec:
		state=waitoff;
		break;

		case res:
		state = waitoff;
		break;

		case waitoff:
		if(input == 0x01){
			state = inc;
			} else if(input == 0x02){
			state = dec;
			} else if(input == 0x03){
			state = res;
			} else {
			state = wait;
		}
		break;

		default:
		state = Start;
		break;
	}


	switch(state){
		case Start:
		break;

		case inc:
		tempC = tempC + 1;
		if(tempC > 9){
			tempC = 9;
		}
		break;

		case dec:
		tempC = tempC - 1;
		if(tempC > 9){
			tempC = 0;
		}
		break;

		case wait:
		break;

		case res:
		tempC = 0x00;
		break;

		default:
		break;
	}

	LCD_Cursor(1);
	LCD_WriteData('0' + tempC);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	
	TimerSet(150);
	TimerOn();
	
	LCD_init();

	while (1)
	{
		tickButton();
		while (!TimerFlag){};
		TimerFlag = 0;
		
		
	}
}