/*    Partner(s) Name & E-mail: Kristian De Castro kdec001@ucr.edu
 *    Lab Section: 024
 *    Assignment: Lab 5  Exercise 2
 *
 *
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */ 

#include <avr/io.h>

enum states{Start, wait, inc, dec, res, waitoff} state;


unsigned char tempC = 0x00;

void tickButton(){
    unsigned char input = (~PINA) & 0x03;
	

    switch(state){
        case Start:
        state = wait;
        tempC = 0x07;
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
            state = waitoff;
        } else if(input == 0x02){
            state = waitoff;
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
        PORTC = tempC;
        break;

        default:
        break;
    }

    PORTC = tempC;
}

int main(void){
        DDRA = 0x00; PORTA = 0xFF;
        DDRC = 0xFF; PORTC = 0x00;

        state = Start;
    while(1){
        tickButton();
    }
}