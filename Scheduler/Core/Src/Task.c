/*
 * Task.c
 *
 *  Created on: Oct 20, 2024
 *      Author: Genki
 */
#include "Task.h"
#include "main.h"

void InitLED(void){
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, SET);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, SET);
	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, SET);
	HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, SET);
	HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, SET);
}
void Task1(void){
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}
void Task2(void){
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}
void Task3(void){
	HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
}
void Task4(void){
	HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}
void Task5(void){
	HAL_GPIO_TogglePin(LED5_GPIO_Port, LED5_Pin);
}

