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
void task1(void){
	HAL_GPIO_TogglePin(LED8_GPIO_Port, LED8_Pin);
}
void task2(void){
	HAL_GPIO_TogglePin(LED9_GPIO_Port, LED9_Pin);
}
void task3(void){
	HAL_GPIO_TogglePin(LED10_GPIO_Port, LED10_Pin);
}
void task4(void){
	HAL_GPIO_TogglePin(LED11_GPIO_Port, LED11_Pin);
}
void task5(void){
	HAL_GPIO_TogglePin(LED12_GPIO_Port, LED12_Pin);
}
