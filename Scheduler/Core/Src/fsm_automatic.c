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
int mode2_flag = 0;
int mode3_flag = 0;
int mode4_flag = 0;
int Time_red = 50;
int Time_green = 30;
int Time_yellow = 20;
int counter_x = 0;
int counter_y = 0;
void SetMode(void){
	if(ProcessButton3() == 1){
		if(counterMode == 2){
			Time_red = counterTimeSet * 10;
			if(Time_red <= Time_green || Time_red <= Time_yellow){
				Time_red = Time_green + Time_yellow;
			}
			else{
				Time_green = Time_red - Time_yellow;
			}
			number_clock1 = Time_red;
			number_clock2 = Time_green;
		}
		if(counterMode == 3){
			Time_green = counterTimeSet * 10;
			if(Time_red <= Time_green){
				Time_red =  Time_yellow + Time_green;
			}
			else{
				Time_yellow = Time_red - Time_green;
			}
			number_clock1 = Time_red;
			number_clock2 = Time_green;
		}
		if(counterMode == 4){
			Time_yellow = counterTimeSet * 10;
			if(Time_red <= Time_yellow){
				Time_red =  Time_yellow + Time_green;
			}
			else{
				Time_green = Time_red - Time_yellow;
			}
			number_clock1 =  Time_red;
			number_clock2 = Time_green;
		}
	}
}
void ChangeModeX(void){
	if(counterMode == 1){
		mode4_flag = 0;
	}
	if(counterMode == 2){
		statusx = MAN_RED;
		InitLED();
	}
	if(counterMode == 3){
		mode2_flag = 0;
		statusx = MAN_GREEN;
		InitLED();
	}
	if(counterMode == 4){
		mode3_flag = 0;
		statusx = MAN_YELLOW;
		InitLED();
	}
}
void ChangeModeY(void){
	if(counterMode == 1){
		mode4_flag = 0;
	}
	if(counterMode == 2){
		statusy = MAN_RED;
		InitLED();
	}
	if(counterMode == 3){
		mode2_flag = 0;
		statusy = MAN_GREEN;
		InitLED();
	}
	if(counterMode == 4){
		mode3_flag = 0;
		statusy = MAN_YELLOW;
		InitLED();
	}
}
void fsm_clock(void){
	if(statusx != MAN_GREEN && statusx != MAN_RED && statusx != MAN_YELLOW){
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
	if(statusx != MAN_GREEN && statusx != MAN_RED && statusx != MAN_YELLOW){
		number_clock1--;
	}
}
void clockY(void){
	if(statusx != MAN_GREEN && statusx != MAN_RED && statusx != MAN_YELLOW){
		number_clock2--;
	}
}
void fsm_mode(void){
	if(statusx == MAN_GREEN || statusx == MAN_RED || statusx == MAN_YELLOW){
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
		counter_x = Time_red;
		number_clock1 = counter_x/10;
		break;
	case AUTO_RED:
		DisplayREDX();
		SetMode();
		ChangeModeX();
		if(counter_x == 0){
			InitLED();
			statusx = AUTO_GREEN;
			counter_x = Time_green;
			number_clock1 = counter_x/10;
		}
		break;
	case AUTO_GREEN:
		DisplayGREENX();
		SetMode();
		ChangeModeX();
		if(counter_x == 0){
			InitLED();
			statusx = AUTO_YELLOW;
			counter_x = Time_yellow;
			number_clock1 = counter_x/10;
		}
		break;
	case AUTO_YELLOW:
		DisplayYELLOWX();
		SetMode();
		ChangeModeX();
		if(counter_x == 0){
			InitLED();
			statusx = AUTO_RED;
			counter_x = Time_red;
			number_clock1 = counter_x/10;
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
		counter_y = Time_green;
		number_clock2 = counter_y/10;
		break;
	case AUTO_RED:
		DisplayREDY();
		SetMode();
		ChangeModeY();
		if(counter_y == 0){
			InitLED();
			statusy = AUTO_GREEN;
			counter_y = Time_green;
			number_clock2 = counter_y/10;
		}
		break;
	case AUTO_GREEN:
		DisplayGREENY();
		SetMode();
		ChangeModeY();
		if(counter_y == 0){
			InitLED();
			statusy = AUTO_YELLOW;
			counter_y = Time_yellow;
			number_clock2 = counter_y/10;
		}
		break;
	case AUTO_YELLOW:
		DisplayYELLOWY();
		SetMode();
		ChangeModeY();
		if(counter_y == 0){
			InitLED();
			statusy = AUTO_RED;
			counter_y = Time_red;
			number_clock2 = counter_y/10;
		}
		break;
	default:
		break;
	}
	if(counter_y > 0){
		counter_y--;
	}
}
