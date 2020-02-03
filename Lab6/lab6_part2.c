/*    Partner(s) Name & E-mail: Kristian De Castro kdec001@ucr.edu
 *    Lab Section: 024
 *    Assignment: Lab 6  Part 2
 *
 *
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */ 

#include <avr/io.h>


#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1
unsigned long _avr_timer_M = 1; // start count from here, down to 0. default 1 ms
unsigned long _avr_timer_cntcurr = 0; // current internal count of 1ms ticks

void TimerOn(){
	TCCR1B = 0x0B; //bit 3 = 0 : CTC mode (clear timer on compare)
	
	//AVR output compare register OCR1A
	OCR1A = 125; // Timer interrupt will be generated when TCNT1 == OCR1A
	// want a 1 ms tick. 0.001 s * 125,000 tick/s
	
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	
	SREG |= 0x80;
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}


enum blStates{start, wait, on, off, /*waitAgain*/} state;

unsigned char check = 0x00;

void blinkTick(){
	
	unsigned char button = ~PINA & 0x01;
	
	switch(state){
		case start:
		state = wait;
		break;
		
		case wait:
		if(button == 0x01){
			state = off;
		} else {
			state = on;
		}
		
		break;
		
		case on:
		if(button == 0x01){
			state = off;
		} else {
			state = wait;	
		}
		break;
		
		case off:
		if(button == 0x01){
			state = wait;
		} else {
			state = off;
		}
		break;
		
// 		case waitAgain:
// 		if(button == 0x01){
// 			state = wait;
// 		} else {
// 			state = waitAgain;
// 		}
// 		break;
		
		default:
		state = start;
		break;
	}
	
	switch(state){
		case start:
		check = 0;
		break;
		
		case wait:
		if(check == 0){
			PORTB = 0x01;
		} else if (check == 1){
			PORTB = 0x02;
		} else if (check == 2){
			PORTB = 0x04;
		} else if (check == 3){
			PORTB = 0x02;
		}
		check++;
		if(check == 4){
			check = 0;
		}
		
		case on:
		break;
		
		case off:
		break;
		
// 		case waitAgain:
// 		break;
		
		default:
		break;
	}
	
}

int main(){
	DDRA = 0x00;
	PORTA= 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(400);
	TimerOn();
	unsigned char tmpB = 0x00;
	while(1){
		tmpB = ~tmpB;
		blinkTick();
		while(!TimerFlag);
		TimerFlag = 0;
	}
}


