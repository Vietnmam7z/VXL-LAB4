/*
 * Scheduler.h
 *
 *  Created on: Oct 20, 2024
 *      Author: Genki
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
typedef struct{
void (* pTask )(void);
	uint32_t Delay ;
	uint32_t Period ;
	uint8_t RunMe;
	uint32_t TaskID ;
}sTask;
#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0
void Timer_init(void);

void Watchdog_init(void);

void SCH_Init(void);

unsigned char SCH_Add_Task (void (*pFunction)(), unsigned int Delay, unsigned int Period);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);

uint8_t SCH_Delete_Task(uint32_t TASK_INDEX);

void SCH_Go_To_Sleep(void);

void SCH_Report_Status(void);

#endif /* INC_SCHEDULER_H_ */
