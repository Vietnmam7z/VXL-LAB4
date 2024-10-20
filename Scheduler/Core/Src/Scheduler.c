/*
 * Scheduler.c
 *
 *  Created on: Oct 20, 2024
 *      Author: Genki
 */
#include "Scheduler.h"

unsigned char Error_code_G = 0;
#define ERROR_SCH_TOO_MANY_TASKS 1
#define ERROR_SCH_WAITING_FOR_SLAVE_TO_ACK 2
#define ERROR_SCH_WAITING_FOR_START_COMMAND_FROM_MASTER 3
#define ERROR_SCH_ONE_OR_MORE_SLAVES_DID_NOT_START 4
#define ERROR_SCH_LOST_SLAVE 5
#define ERROR_SCH_CAN_BUS_ERROR 6
#define ERROR_I2C_WRITE_BYTE_AT24C64 7
#define ERROR_SCH_CANNOT_DELETE_TASK 8
#define RETURN_ERROR 9
#define RETURN_NORMAL 10
sTask SCH_tasks_G[SCH_MAX_TASKS];
void Timer_init(void){

}
void Watchdog_init(void){

}
void SCH_Init(void){
	unsigned char i ;
	for (i = 0; i < SCH_MAX_TASKS;i++) {
		SCH_Delete_Task(i);
	}
	Error_code_G = 0;
	Timer_init();
	Watchdog_init();
}
void SCH_Update(void){
	unsigned char Index;
	for(Index = 0; Index < SCH_MAX_TASKS; Index++){
		if(SCH_tasks_G[Index].pTask){
			if(SCH_tasks_G[Index].Delay == 0){
				SCH_tasks_G[Index].RunMe += 1;
				if(SCH_tasks_G[Index].Period){
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
				}
			}
			else{
				SCH_tasks_G[Index].Delay--;
			}
		}
	}
}
unsigned char SCH_Add_Task(void(*pFunction)() , unsigned int DELAY,unsigned int PERIOD){
	unsigned char Index = 0;
	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)){
		Index++;
	}
	if(Index == SCH_MAX_TASKS){
		Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
		return SCH_MAX_TASKS;
	}
	SCH_tasks_G[Index].pTask = pFunction;
	SCH_tasks_G[Index].Delay = DELAY;
	SCH_tasks_G[Index].Period = PERIOD;
	SCH_tasks_G[Index].RunMe = 0;
	return Index;
}
void SCH_Dispatch_Tasks(void){
	unsigned char Index ;
	for(Index = 0; Index < SCH_MAX_TASKS; Index++){
		if(SCH_tasks_G [Index].RunMe > 0){
			(*SCH_tasks_G[Index].pTask)();
			SCH_tasks_G[Index].RunMe--;
			if(SCH_tasks_G[Index].Period == 0){
				SCH_Delete_Task(Index);
			}
		}
	}
	SCH_Report_Status();
	SCH_Go_To_Sleep();
}
uint8_t SCH_Delete_Task(const uint32_t TASK_INDEX){
	unsigned char Return_code;
	if(SCH_tasks_G[TASK_INDEX].pTask == 0){
		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		Return_code = RETURN_ERROR;
	}
	else{
		Return_code = RETURN_NORMAL;
	}
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;
	return Return_code;
}
void SCH_Go_To_Sleep(void){
//todo
}
void SCH_Report_Status(void){
#ifdef SCH_REPORT_ERRORS
	if(Error_code_G != Last_error_code_G){
		Error_port = 255 − Error_code_G;
		Last_error_code_G = Error_code_G ;
		if(Error_code_G != 0){
			Error_tick_count_G = 60000;
		}
		else{
			Error_tick_count_G = 0;
		}
	}
	else{
		if(Error_tick_count_G != 0){
			if(−−Error_tick_count_G == 0 ){
				Error_code_G = 0;
			}
		}
	}
#endif
}


