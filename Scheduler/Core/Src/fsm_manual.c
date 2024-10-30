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
	case CONF_RED:
		if(counter_led_x == 0){
			DisplayMAN_REDX();
			counter_led_x = 5;
		}
		if(counterMode == 3){
			statusx = CONF_GREEN;
			InitLED();
		}
		SetMode();
		if(mode2_flag == 1){
			statusx = MAN_RED;
			counter_x = save_counterTimeSet*10;
			number_clock1 = counter_x/10;
			statusy = AUTO_GREEN;
			counter_y = save_counterTimeSet*10 - 20;
			number_clock2 = counter_y/10;
			InitLED();
		}
		break;
	case MAN_RED:
		if(counterMode != 2){
			DisplayREDX();
		}
		else{
			if(counter_led_x == 0){
				DisplayMAN_REDX();
				counter_led_x = 5;
			}
		}
		ChangeModeX();
		fsm_clock();
		if(counter_x == 0){
			InitLED();
			statusx = AUTO_GREEN;
			if(mode2_flag == 1){
				counter_x = save_counterTimeSet*10 - 20;
			}
			else{
				counter_x = 30;
			}
			number_clock1 = counter_x/10;
		}
		break;
	case CONF_GREEN:
		if(counter_led_x == 0){
			DisplayMAN_GREENX();
			counter_led_x = 5;
		}
		if(counterMode == 4){
			statusx = CONF_YELLOW;
			InitLED();
		}
		SetMode();
		if(mode3_flag == 1){
			statusx = AUTO_RED;
			counter_x = save_counterTimeSet*10 + 20;
			number_clock1 = counter_x/10;
			statusy = MAN_GREEN;
			counter_y = save_counterTimeSet*10;
			number_clock2 = counter_y/10;
			InitLED();
		}
		break;
	case MAN_GREEN:
		if(counterMode != 3){
			DisplayGREENX();
		}
		else{
			if(counter_led_x == 0){
				DisplayMAN_GREENX();
				counter_led_x = 5;
			}
		}
		ChangeModeX();
		fsm_clock();
		if(counter_x == 0){
			InitLED();
			statusx = AUTO_YELLOW;
			if(mode2_flag == 1){
				if(save_counterTimeSet < 2){
					counter_x = save_counterTimeSet*10;
				}
			}
			else{
				counter_x = 20;
			}
			number_clock1 = counter_x/10;
		}
		break;
	case CONF_YELLOW:
		if(counter_led_x == 0){
			DisplayMAN_YELLOWX();
			counter_led_x = 50;
		}
		if(counterMode == 1){
			statusx = AUTO_RED;
			counter_x = 50;
			number_clock1 = counter_x/10;
			InitLED();
		}
		SetMode();
		if(mode4_flag == 1){
			statusx = MAN_RED;
			counter_x = save_counterTimeSet*10 + 30;
			number_clock1 = counter_x/10;
			statusy = AUTO_GREEN;
			counter_y = 30;
			number_clock2 = counter_y/10;
			InitLED();
		}
		break;
	case MAN_YELLOW:
		if(counterMode != 4){
			DisplayYELLOWX();
		}
		else{
			if(counter_led_x == 0){
				DisplayMAN_YELLOWX();
				counter_led_x = 5;
			}
		}
		ChangeModeX();
		fsm_clock();
		if(counter_x == 0){
			InitLED();
			statusx = AUTO_RED;
			if(mode3_flag == 1){
				counter_x = save_counterTimeSet*10 + 20;
			}
			else if(mode4_flag == 1){
				counter_x = save_counterTimeSet*10 + 30;
			}
			else{
				counter_x = 50;
			}
			number_clock1 = counter_x/10;
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
	case CONF_RED:
		if(counter_led_y == 0){
			DisplayMAN_REDY();
			counter_led_y = 5;
		}
		if(counterMode == 3){
			statusy = CONF_GREEN;
			InitLED();
		}
		break;
	case MAN_RED:
		if(counterMode != 2){
			DisplayREDY();
		}
		else{
			if(counter_led_y == 0){
				DisplayMAN_REDY();
				counter_led_y = 5;
			}
		}
		ChangeModeY();
		if(counter_y == 0){
			InitLED();
			statusy = AUTO_GREEN;
			if(mode2_flag == 1){
				counter_y = save_counterTimeSet*10 - 20;
			}
			else{
				counter_y = 30;
			}
			number_clock2 = counter_y/10;
		}
		break;
	case CONF_GREEN:
		if(counter_led_y == 0){
			DisplayMAN_GREENY();
			counter_led_y = 5;
		}
		if(counterMode == 4){
			statusy = CONF_YELLOW;
			InitLED();
		}
		break;
	case MAN_GREEN:
		if(counterMode != 3){
			DisplayGREENY();
		}
		else{
			if(counter_led_y == 0){
				DisplayMAN_GREENY();
				counter_led_y = 5;
			}
		}
		ChangeModeY();
		if(counter_y == 0){
			InitLED();
			statusy = AUTO_YELLOW;
			if(mode2_flag == 1){
				if(save_counterTimeSet < 2){
					counter_y = save_counterTimeSet*10;
				}
			}
			else{
				counter_y = 20;
			}
			number_clock2 = counter_y/10;
		}
		break;
	case CONF_YELLOW:
		if(counter_led_y == 0){
			DisplayMAN_YELLOWY();
			counter_led_y = 5;
		}
		if(counterMode == 1){
			statusy = AUTO_GREEN;
			counter_y = 30;
			InitLED();
		}
		break;
	case MAN_YELLOW:
		if(counter_led_y == 0){
			DisplayMAN_YELLOWY();
			counter_led_y = 5;
		}
		ChangeModeY();
		if(counter_y == 0){
			InitLED();
			statusy = AUTO_RED;
			if(mode3_flag == 1){
				counter_y = save_counterTimeSet*10 + 20;
			}
			else if(mode4_flag == 1){
				counter_y = save_counterTimeSet*10 + 30;
			}
			else{
				counter_y = 50;
			}
			number_clock2 = counter_y/10;
		}
		break;
	default:
		break;
	}
	if(counter_led_y > 0){
		counter_led_y--;
	}
}
