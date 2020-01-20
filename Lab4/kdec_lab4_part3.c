/*	Partner(s) Name & E-mail: Kristian De Castro kdec001@ucr.edu 
 *	Lab Section: 024
 *	Assignment: Lab 4  Exercise 3
 *	
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */ 


#include <avr/io.h>

enum lockSM{start, wait, pound, ypress, unlock, lock} state;
// X			-> 0001 -> 0x01				BIT 0
// Y			-> 0010 -> 0x02				BIT 1
// POUND		-> 0100 -> 0x04				BIT 2
// LOCK BUTTON	-> 1000 -> 0x80;			BIT 7


void lockTick(){
	unsigned char combo = PINA & 0x87;
	switch(state){
		
		case start:					//initial state
		state = wait;  
		break;
		
		case wait:				//waiting state
		if(combo == 0x04){		//user press pound
			state = pound;
		} else if (combo == 0x02){	//user presses Y but goes to lock
			state = lock;
		} else if (combo == 0x80){	//user locks the door by pressed PA7
			state = lock;
		} else {
			state = wait;
		}
		break;
		
		case pound:
		if(combo == 0x04){ //user pressed pound again, resets back to pound
			state = pound;
		} else if (combo == 0x02){ //user presses Y to unlock door
			state = ypress;
		} else if (combo == 0x01){ //user presses X, door resets
			state = lock;
		} else if (combo == 0x08){ //user locks door anyway
			state = lock;
		} else {
			state = pound;
		}
		break;
		
		case ypress:
		if(combo == 0x04){
			state = wait;
		} else if (combo == 0x02){
			state = ypress;
		} else {
			state = unlock;
		}
		break;
		
		case unlock:
		state = wait;
		break;
		
		case lock:
		if(combo == 0x80){
			state = lock;
		} else {
			state = wait;
		}
		break;
		
		default:
		state = wait;
		break;
	}
	
	switch(state){
		case start:
		break;
		
		case wait:
		break;
		
		case pound:
		break;
		
		case ypress:
		break;
		
		case unlock:
		PORTB = 0x01;
		break;
		
		case lock: 
		PORTB = 0x00;
		break;
		
		default:
		PORTB = 0x00;
		break;
		
		
	}
}

int main(void){
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	while(1){
		lockTick();
	}
	
	return 0;
}
