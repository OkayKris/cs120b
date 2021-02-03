/*
 * reactiongame.c
 *
 * Created: 3/5/2020 2:57:22 PM
 * Author : okayk
 */ 


#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "io.h"
#include "io.c"
#include <devices/AVR8.h>
#include <devices/AVR8.c>
#include <controllers/PCD8544.h>
#include <controllers/PCD8544.c>
#include <glcd_controllers.h>
#include <glcd_devices.h>
#include <glcd.h>
#include <glcd.c>
#include <fonts/font5x7.h>
#include <glcd_graphics.h>
#include <glcd_graphs.h>
#include <glcd_text.h>
#include <glcd_text_tiny.h>
#include <text.c>
#include <text_tiny.c>
#include <graphs.c>
#include <graphics.c>
#include <unit_tests.h>
#include <unit_tests.c>
#include "customChar.h"
#include "timer.h"
#include "snes.c"
//#include "Apple_Logo.h"
//#include "sans.h"

//State enums
enum game{wait, play ,contplay,/* diff,*/ score, gameOver} stateG;

//Globals
const unsigned long SystemPeriod = 1;
unsigned char gg = 0;
unsigned char point = 0;


void buildmenu(){ //Menu build on Nokia Screen
	
	glcd_init();
	glcd_set_contrast(210);
	glcd_tiny_set_font(Font5x7, 5, 7, 32, 127);
	glcd_clear_buffer();
	glcd_tiny_draw_string(15, 0, "Main Menu");
	glcd_draw_line(12,7,70,7,1);
	
	glcd_tiny_draw_string(10,2, "Play(START)");
	/*glcd_tiny_draw_string(15,3, "Diff(SEL)");*/
	glcd_tiny_draw_string(18,4, "Score(X)");
	glcd_write();

	LCD_init();	
	LCD_ClearScreen();
	LCD_DisplayString(1, "Welcome to Taiko Mania!");
	LCD_Cursor(20);
	
}


//  SNES_NONE        0
//  SNES_R          16
//  SNES_L         	32
//  SNES_X          64
//  SNES_A         128
//  SNES_RIGHT     256
//  SNES_LEFT      512
//  SNES_DOWN     1024
//  SNES_UP       2048
//  SNES_START    4096
//  SNES_SELECT   8192
//  SNES_Y       16384
//  SNES_B       32768

void buildGame(/*Note N*/){
	LCD_init();
	LCD_ClearScreen();
	LCD_DisplayString(1, "Score: ");
	LCD_Cursor(20);
	LCD_WriteData(4);
	LCD_Cursor(22);
	LCD_WriteData(4);
}

unsigned char gameFlag = 0;
unsigned short gameCount = 0;
unsigned short maxscore;
unsigned char lives = 5;

//Menu tasks to go play, change difficulty, or show the high score
void gameTask (/*int stateG*/){
	unsigned short press = SNES_Read();
	unsigned int check = rand() % 4;
	unsigned char note;
	unsigned readFlag = 0;
	
	maxscore = (unsigned)(char)eeprom_read_byte((uint8_t*)1);
	char buffer[20];
	switch(stateG){ //ACTIONS
		case wait: //TBD: MAIN MENU
		//eeprom_update_byte((uint8_t*)1, (uint8_t)0); //MAX SCORE HARD RESET
		point = 0;
		gg = 0;
		gameCount = 0;
		lives = 5;
		break;
		case play: //TBD: SWITCH TO GAMEPLAY
		/*buildGame();*/
		
		LCD_Cursor(32);
		break;
		case contplay:
		
		if(check == 0){
			gameFlag = 1;
			note = 1;
		} else if(check == 1) {
			gameFlag = 2;
			note = 0;
		}else if(check == 2) {
			gameFlag = 3;
			note = 2;
		}else {
			gameFlag = 4;
			note = 3;
		}

// 		LCD_Cursor(13);
// 		LCD_WriteData(4);
// 		LCD_Cursor(14);
// 		LCD_WriteData(':');
// 		LCD_DisplayString(15, lives);
		itoa(point, buffer, 10);
		unsigned char disp[10] = "Score: ";
		strcat(disp, buffer);
		LCD_DisplayString(1, disp);
		
		
		
		
		if(check == 0){
			LCD_Cursor(17);
			delay_ms(5000);
			LCD_WriteData(note);
			delay_ms(3750);
		} else if (check == 1){
			LCD_Cursor(22);
			delay_ms(5000);
			LCD_WriteData(note);
			delay_ms(3750);
		}else if (check == 2){
			LCD_Cursor(27);
			delay_ms(5000);
			LCD_WriteData(note);
			delay_ms(3750);
		}else if (check == 3){
			LCD_Cursor(32);
			delay_ms(5000);
			LCD_WriteData(note);
			delay_ms(3750);
		}
		
		
		
// 		while(count < 20000){
// 			delay_ms(1);
// 
// 			if((press & 128) && (note == 0)){
// 				readFlag = 1;
// 				break;
// 				} else {
// 				//readFlag = 0;
// 				//break;
// 			}
// 			
// 			
// 			if((press & 64) && (note == 2)){
// 				readFlag = 1;
// 				break;
// 				} else {
// 				//readFlag = 0;
// 				//break;
// 			}		
// 			
// 			count++;	
// 		}
// 		
// 		if(readFlag == 1){
// 			point++;
// 			
// 			
// 		}
// 		LCD_Cursor(24);
// 		LCD_WriteData(' ');
// 		delay_ms(10000);
		if(point > maxscore){
			maxscore = point;
			eeprom_update_byte((uint8_t*)1, (uint8_t)maxscore);
		}
		break;
// 		case diff: //TBD: SWITCH SCREEN TO THREE DIFFICULTIES
// 		
// 		break;
		case score: //TBD: SWITCH SCREEN TO SHOW HIGHSCORE
		LCD_init();
		LCD_ClearScreen();
		LCD_DisplayString(1, "High Score: ");
		LCD_Cursor(18);
		if(maxscore <= 9) {
			LCD_WriteData('0' + maxscore);
		}
		else if((maxscore > 9) && (maxscore <= 19)) {
			LCD_Cursor(18);
			LCD_WriteData('1');
			LCD_WriteData('0' + (maxscore - 10));
		}
		else if((maxscore > 19) && (maxscore <= 29)) {
			LCD_Cursor(18);
			LCD_WriteData('2');

			LCD_WriteData('0' + (maxscore - 20));
		}
		break;
		case gameOver:
		if(point > maxscore){
			maxscore = point;
			eeprom_update_byte((uint8_t*)1, (uint8_t)point);
		}
		LCD_init();
		LCD_ClearScreen();
		LCD_DisplayString(1,"Game Over!!");
		break;
		default: //DEFAULT IS ... menu?
		break;
	}
	
	switch(stateG){ //TRANSITIONS
		case wait:
		if(press & 4096){
			stateG = contplay;
		} else if (press & 8192){
			//stateG = diff;
		} else if (press & 64){
			stateG = score;
		} else {
			stateG = wait;
		}
		break;
		case play:
		stateG = contplay;
		break;
		case contplay:
		if(gg < 5){
			stateG = contplay;
		} else if (gg > 5){
			gg = 0;
			stateG = gameOver;
		}
		break;
// 		case diff:
// 		break;
		case score:
		if(press & 64){
			stateG = wait;
		}
		break;
		case gameOver:
		
		if(press & 128){
			LCD_DisplayString(1, "Welcome to Taiko Mania!");
			stateG = wait;
		} else {
			stateG = gameOver;
		}
		delay_ms(100);
		break;
		default:
		break;
	}
	/*return stateG;*/
}


unsigned short keyCount = 0;
unsigned char keyFlag = 0;
enum keyState { waiton, a, x, l, r, waitoff} stateK;
	
void keyTick(/*int stateK*/){
	maxscore = (unsigned)(char)eeprom_read_byte((uint8_t*)1);
	unsigned short press = SNES_Read();
	switch(stateK){
		case waiton:
		if(press & 2048){
			stateK = a;
		} else if (press & 1024){
			stateK = x;
		} else if (press & 512){
			stateK = l;
		} else if (press & 256){
			stateK = r;
		} else {
			stateK = waiton;
		}
		break;
		
		case waitoff:
		if(press & 2048){
			stateK = a;
		} else if (press & 1024){
			stateK = x;
		} else if (press & 512){
			stateK = l;
		} else if (press & 256){
			stateK = r;
		} else {
			stateK = waiton;
		}
		break;
		
		case a:
		stateK = waitoff;
		break;
		
		case x:
		stateK = waitoff;
		break;
		
		case l:
		stateK = waitoff;
		break;
		
		case r:
		stateK = waitoff;
		break;
		
		default:
		stateK = waiton;
		break;
	}
	
	switch(stateK){
		case waiton:
		keyFlag = 0;
		break;
		
		case waitoff:
		break;
		
		case a:
		keyFlag = 2;
		break;
		
		case x:
		keyFlag = 3;
		break;
		
		case l:
		keyFlag = 1;
		break;
		
		case r:
		keyFlag = 4;
		break;
		
		default:
		break;
	}
	/*return stateK;*/
}

enum playTick {game1, game2} playState;
void playGame(/*int playState*/){
	
	switch(playState){
		case game1:
		playState = game2;

		break;
		
		case game2:
		playState = game1;
		break;
		
		default:
		break;
	}
	
	switch(playState){
		case game1:
		if(keyFlag == gameFlag){
// 			LCD_Cursor(20);
// 			LCD_WriteData(' ');
			point++;
		} else {
			gg++;
			lives--;
		}
		
		break;
		
		case game2:
		if(keyFlag == gameFlag){
// 			LCD_Cursor(28);
// 			LCD_WriteData(' ');
			point++;
		} else {
			gg++;
			lives--;
		}
		break;
		
		default:
		break;
	}
	
	
	/*return playState;*/
}



int main(void)
{
	DDRA = 0x03; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	srand(time(0));
	TimerSet(SystemPeriod);
	TimerOn();
	
	
	
	glcd_init();
	glcd_tiny_set_font(Font5x7, 5,7,32,127);
	glcd_clear_buffer();
	LCD_init();
	LCD_ClearScreen();
	LCD_Cursor(1);
	buildmenu();
	
	
	/*Note N = NoteInit();*/
	LCD_Custom_Char(0, aNote);  /* Build Character1 at position 0 */
	LCD_Custom_Char(1, left);  /* Build Character2 at position 1 */
	LCD_Custom_Char(2, xNote);  /* Build Character3 at position 2 */
	LCD_Custom_Char(3, right);  /* Build Character4 at position 3 */
	LCD_Custom_Char(4, heart);  /* Build Character5 at position 4 */
	
	
// 	unsigned long int tempGCD = tasks[0].period;
// 
// 	for(unsigned char i=1;i<taskNum;i++){
// 		tempGCD = findGCD(tempGCD,tasks[i].period);
// 	}
// 	unsigned char j = 0;
// 	tasks[j].state = stateG;
// 	tasks[j].period = 1000;
// 	tasks[j].elapsedTime = tasks[i].period;
// 	tasks[j].TickFct = &gameTask;
// 	j++;
// 	
// 	tasks[j].state = stateK;
// 	tasks[j].period = 1;
// 	tasks[j].elapsedTime = tasks[i].period;
// 	tasks[j].TickFct = &keyTick;
// 	j++;
// 	
// 	tasks[j].state = playState;
// 	tasks[j].period = 1;
// 	tasks[j].elapsedTime = tasks[i].period;
// 	tasks[j].TickFct = &playGame;
// 	j++;


    while (1) 
    {
		
// 		for(unsigned short i = 0; i < taskNum; i++){
// 			if(tasks[i].elapsedTime == tasks[i].period){
// 				tasks[i].state = tasks[i].TickFct(tasks[i].state);
// 				tasks[i].elapsedTime = 0;
// 			}
// 			tasks[i].elapsedTime = tempGCD;
// 		}

		gameTask();
		keyTick();
		playGame();
		
		while(!TimerFlag);
		TimerFlag = 0;


    }
}

