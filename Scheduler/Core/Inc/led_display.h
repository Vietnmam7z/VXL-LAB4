/*
 * led_display.h
 *
 *  Created on: Sep 27, 2024
 *      Author: Genki
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_
void Display7Seg(int x);
void Display(int x);
void DisplayREDX(void);
void DisplayYELLOWX(void);
void DisplayGREENX(void);
void DisplayREDY(void);
void DisplayYELLOWY(void);
void DisplayGREENY(void);
void DisplayMAN_REDX(void);
void DisplayMAN_REDY(void);
void DisplayMAN_GREENX(void);
void DisplayMAN_GREENY(void);
void DisplayMAN_YELLOWX(void);
void DisplayMAN_YELLOWY(void);
void InitLED(void);
#endif /* INC_LED_DISPLAY_H_ */
