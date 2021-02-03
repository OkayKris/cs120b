#ifndef CUSTOMCHAR_H
#define CUSTOMCHAR_H


char i;
	
	
/* Custom char set for alphanumeric LCD Module */
unsigned char aNote[8] = { 0x00,
	 0x04,
	 0x0E,
	 0x15,
	 0x15,
	 0x04,
	 0x04,
	 0x04,
	 0x04 };
unsigned char left[8] = { 0x1F,
	0x00,
	0x04,
	0x08,
	0x1F,
	0x08,
	0x04,
	0x00,
	0x00 };
unsigned char xNote[8] = { 0x00,
	 0x04,
	 0x04,
	 0x04,
	 0x15,
	 0x15,
	 0x0E,
	 0x04,
	 0x00 };
unsigned char right[8] = { 0x1F,
	0x00,
	0x04,
	0x02,
	0x1F,
	0x02,
	0x04,
	0x00,
	0x00 };
unsigned char heart[8] = { 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00 };
// 	unsigned char Character6[8] = { 0x0A, 0x0A, 0x1F, 0x11, 0x11, 0x0E, 0x04, 0x04 }; Unnecessary characters
// 	unsigned char Character7[8] = { 0x00, 0x00, 0x0A, 0x00, 0x04, 0x11, 0x0E, 0x00 };
// 	unsigned char Character8[8] = { 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00 };




// 	LCD_Custom_Char(5, Character6);  /* Build Character6 at position 5 */
// 	LCD_Custom_Char(6, Character7);  /* Build Character6 at position 6 */
// 	LCD_Custom_Char(7, Character8);  /* Build Character6 at position 7 */


#endif //CUSTOMCHAR_H