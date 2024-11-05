/*
 * fsm_manual.c
 *
 *  Created on: 29 Sep 2024
 *      Author: Genki
 */

#include "fsm_manual.h"
#include "led_display.h"
#include "input_processing.h"
#include "fsm_automatic.h"
int counter_led_x = 0;
int counter_led_y = 0;
void fsm_manual_run1(void){
	switch(statusx){
	case MAN_RED:
		if(counter_led_x == 0){
			DisplayMAN_REDX();
			counter_led_x = 5;
		}
		if(counterMode == 3){
			statusx = MAN_GREEN;
			InitLED();
		}
		SetMode();
		break;
	case MAN_GREEN:
		if(counter_led_x == 0){
			DisplayMAN_GREENX();
			counter_led_x = 5;
		}
		SetMode();
		if(counterMode == 4){
			statusx = MAN_YELLOW;
			InitLED();
		}
		break;
	case MAN_YELLOW:
		if(counter_led_x == 0){
			DisplayMAN_YELLOWX();
			counter_led_x = 5;
		}
		SetMode();
		if(counterMode == 1){
			statusx = AUTO_RED;
			number_clock1 = Time_red/10;
			counter_x = Time_red;
			InitLED();
		}
		break;
	default:
		break;
	}
	if(counter_led_x > 0){
		counter_led_x--;
	}
}
void fsm_manual_run2(void){
	switch(statusy){
	case MAN_RED:
		if(counter_led_y == 0){
			DisplayMAN_REDY();
			counter_led_y = 5;
		}
		if(counterMode == 3){
			statusy = MAN_GREEN;
			InitLED();
		}
		break;
	case MAN_GREEN:
		if(counter_led_y == 0){
			DisplayMAN_GREENY();
			counter_led_y = 5;
		}
		if(counterMode == 4){
			statusy = MAN_YELLOW;
			InitLED();
		}
		break;
	case MAN_YELLOW:
		if(counter_led_y == 0){
			DisplayMAN_YELLOWY();
			counter_led_y = 5;
		}
		if(counterMode == 1){
			statusy = AUTO_GREEN;
			number_clock2 = Time_green/10;
			counter_y = Time_green;
			InitLED();
		}
		break;
	default:
		break;
	}
	if(counter_led_y > 0){
		counter_led_y--;
	}
}
