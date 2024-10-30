/*
 * Task.c
 *
 *  Created on: Oct 20, 2024
 *      Author: Genki
 */
#include "Task.h"
#include "main.h"
#include <stdio.h>
#include "global.h"
void Task4(void){
	HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}
void Task5(void){
	HAL_GPIO_TogglePin(LED5_GPIO_Port, LED5_Pin);
}
void get_time(void){
	uint32_t time = HAL_GetTick();
	printf("Time: %lu\n", time);
}
void task_auto_redX(void){
	statusx = AUTO_RED;
}
void task_auto_greenX(void){
	statusx = AUTO_GREEN;
}
void task_auto_yellowX(void){
	statusx = AUTO_YELLOW;
}
void task_auto_redY(void){
	statusy = AUTO_RED;
}
void task_auto_greenY(void){
	statusy = AUTO_GREEN;
}
void task_auto_yellowY(void){
	statusy = AUTO_YELLOW;
}
