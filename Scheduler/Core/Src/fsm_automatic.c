/*
 * fsm_automatic.c
 *
 *  Created on: Sep 28, 2024
 *      Author: Genki
 */

#include "fsm_automatic.h"
#include "input_processing.h"
#include "main.h"
#include "Scheduler.h"
#include "Task.h"
int DisplayCounter = 0;
int mode1_flag = 0;
int mode2_flag = 0;
int mode3_flag = 0;
int mode4_flag = 0;
int save_counterTimeSet = 0;
int counter_x = 0;
int counter_y = 0;
void SetMode(void){
	if(ProcessButton3() == 1){
		if(counterMode == 2){
			mode2_flag = 1;
			mode3_flag = 0;
			mode4_flag = 0;
			save_counterTimeSet = counterTimeSet;
		}
		if(counterMode == 3){
			mode2_flag = 0;
			mode3_flag = 1;
			mode4_flag = 0;
			save_counterTimeSet = counterTimeSet;
		}
		if(counterMode == 4){
			mode1_flag = 1;
			mode2_flag = 0;
			mode3_flag = 0;
			mode4_flag = 1;
			save_counterTimeSet = counterTimeSet;
		}
	}
}
void ChangeModeX(void){
	if(counterMode == 1){
		mode4_flag = 0;
	}
	if(counterMode == 2){
		if(mode2_flag == 0){
			statusx = CONF_RED;
			InitLED();
		}
	}
	if(counterMode == 3){
		mode2_flag = 0;
		if(mode3_flag == 0){
			statusx = CONF_GREEN;
			InitLED();
		}
	}
	if(counterMode == 4){
		mode3_flag = 0;
		if(mode4_flag == 0){
			statusx = CONF_YELLOW;
			InitLED();
		}
	}
}
void ChangeModeY(void){
	if(counterMode == 1){
		mode4_flag = 0;
		if(mode1_flag == 1){
			mode1_flag = 0;
			statusx = AUTO_RED;
			counter_x = 50;
			number_clock1 = counter_x/10;
			statusy = AUTO_GREEN;
			counter_y = 30;
			number_clock2 = counter_y/10;
			InitLED();
		}
	}
	if(counterMode == 2){
		if(mode2_flag == 0){
			statusy = CONF_RED;
			InitLED();
		}
	}
	if(counterMode == 3){
		mode2_flag = 0;
		if(mode3_flag == 0){
			statusy = CONF_GREEN;
			InitLED();
		}
	}
	if(counterMode == 4){
		mode3_flag = 0;
		if(mode4_flag == 0){
			statusy = CONF_YELLOW;
			InitLED();
		}
	}
}
void fsm_clock(void){
	if(statusx != CONF_GREEN && statusx != CONF_RED && statusx != CONF_YELLOW){
		if(DisplayCounter == 0){
			Display7Seg(number_clock2/10);
		}
		else if(DisplayCounter == 1){
			Display7Seg(number_clock2%10);
		}
		else if(DisplayCounter == 2){

			Display7Seg(number_clock1/10);
		}
		else if(DisplayCounter == 3){
			Display7Seg(number_clock1%10);

		}
		Display(DisplayCounter);
		DisplayCounter++;
		if(DisplayCounter > 4){
			DisplayCounter = 0;
		}
	}
}
void clockX(void){
	if(statusx != CONF_GREEN && statusx != CONF_RED && statusx != CONF_YELLOW){
		number_clock1--;
		if(number_clock1 <= 0){
			number_clock1 = counter_x/10 + 1;
		}
	}
}
void clockY(void){
	if(statusx != CONF_GREEN && statusx != CONF_RED && statusx != CONF_YELLOW){
		number_clock2--;
		if(number_clock2 <= 0){
			number_clock2 = counter_y/10 + 1;
		}
	}
}
void fsm_mode(void){
	if(statusx == CONF_GREEN || statusx == CONF_RED || statusx == CONF_YELLOW){
		Display(DisplayCounter);
		if(DisplayCounter == 0){
			Display7Seg(0);
		}
		else if(DisplayCounter == 1){
			Display7Seg(counterMode);
		}
		else if(DisplayCounter == 2){
			Display7Seg(counterTimeSet/10);
		}
		else if(DisplayCounter == 3){
			Display7Seg(counterTimeSet%10);
		}
		DisplayCounter++;
		if(DisplayCounter > 4){
			DisplayCounter = 0;
		}
	}
}
void fsm_automatic_runx(){
	switch(statusx){
	case INIT:
		statusx = AUTO_RED;
		counter_x = 50;
		number_clock1 = counter_x/10;
		break;
	case AUTO_RED:
		DisplayREDX();
		SetMode();
		ChangeModeX();
		if(counter_x == 0){
			if(mode3_flag == 1){
				InitLED();
				statusx = MAN_GREEN;
				counter_x = save_counterTimeSet*10;
				number_clock1 = counter_x/10;
			}
			else{
				statusx = AUTO_GREEN;
				counter_x = 30;
			}
		}
		break;
	case AUTO_GREEN:
		DisplayGREENX();
		SetMode();
		ChangeModeX();
		if(counter_x == 0){
			if(mode4_flag == 1){
				InitLED();
				statusx = MAN_YELLOW;
				counter_x = save_counterTimeSet*10;
				number_clock1 = counter_x/10;
			}
			else{
				statusx = AUTO_YELLOW;
				counter_x = 20;
			}
		}
		break;
	case AUTO_YELLOW:
		DisplayYELLOWX();
		SetMode();
		ChangeModeX();
		if(counter_x == 0){
			if(mode2_flag == 1){
				InitLED();
				statusx = MAN_RED;
				counter_x = save_counterTimeSet*10;
				number_clock1 = counter_x/10;
			}
			else if(mode3_flag == 1){
				statusx = AUTO_RED;
				counter_x = save_counterTimeSet*10 + 20;
				number_clock1 = counter_x/10;
			}
			else if(mode4_flag == 1){
				statusx = AUTO_RED;
				counter_x = save_counterTimeSet*10 + 30;
				number_clock1 = counter_x/10;
			}
			else{
				statusx = AUTO_RED;
				counter_x = 50;
			}
		}
		break;
	default:
		break;
	}
	if(counter_x > 0){
		counter_x--;
	}
}
void fsm_automatic_runy(){
	switch(statusy){
	case INIT:
		statusy = AUTO_GREEN;
		counter_y = 30;
		number_clock2 = counter_y/10;
		break;
	case AUTO_RED:
		DisplayREDY();
		SetMode();
		ChangeModeY();
		if(mode2_flag == 1){
			InitLED();
			statusy = MAN_RED;
			counter_y = save_counterTimeSet*10;
			number_clock2 = counter_y/10;
		}
		if(counter_y == 0){
			if(mode3_flag == 1){
				InitLED();
				statusy = MAN_GREEN;
				counter_y = save_counterTimeSet*10;
				number_clock2 = counter_y/10;
			}
			else{
				statusy = AUTO_GREEN;
				counter_y = 30;
			}
		}
		break;
	case AUTO_GREEN:
		DisplayGREENY();
		SetMode();
		ChangeModeY();
		if(mode3_flag == 1){
			InitLED();
			statusy = MAN_GREEN;
			counter_y = save_counterTimeSet*10;
			number_clock2 = counter_y/10;
		}
		if(counter_y == 0){
			if(mode4_flag == 1){
				InitLED();
				statusy = MAN_YELLOW;
				counter_y = save_counterTimeSet*10;
				number_clock2 = counter_y/10;
			}
			else{
				statusy = AUTO_YELLOW;
				counter_y = 20;
			}
		}
		break;
	case AUTO_YELLOW:
		DisplayYELLOWY();
		SetMode();
		ChangeModeY();
		if(mode4_flag == 1){
			InitLED();
			statusy = MAN_YELLOW;
			counter_y = save_counterTimeSet*10;
			number_clock2 = counter_y/10;
		}
		if(counter_y == 0){
			if(mode2_flag == 1){
				InitLED();
				statusy = MAN_RED;
				counter_y = save_counterTimeSet*10;
				number_clock2 = counter_y/10;
			}
			else if(mode3_flag == 1){
				statusy = AUTO_RED;
				counter_y = save_counterTimeSet*10 + 20;
				number_clock2 = counter_y/10;
			}
			else if(mode4_flag == 1){
				statusy = AUTO_RED;
				counter_y = save_counterTimeSet*10 + 30;
				number_clock2 = counter_y/10;
			}
			else{
			statusy = AUTO_RED;
			counter_y = 50;
			}
		}
		break;
	default:
		break;
	}
	if(counter_y > 0){
		counter_y--;
	}
}
