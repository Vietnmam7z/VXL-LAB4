/*
 * Scheduler.h
 *
 *  Created on: Oct 20, 2024
 *      Author: Genki
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#define SCH_MAX_TASKS 40

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Task {
void (* pTask )(void);
	uint32_t Delay ;
	uint32_t Period ;
	uint8_t RunMe;
	struct Task* next;
}sTask;
typedef struct {
    sTask* head;

} TaskList;

TaskList* createTaskList();

extern TaskList* list;

void Timer_init(void);

void Watchdog_init(void);

TaskList* createTaskList();

void SCH_Init(void);

void SCH_Add_Task(void (*pTask)(void), uint32_t delay, uint32_t period);

void SCH_Update(void);

sTask* Enqueue(sTask* newTask);

void SCH_Dispatch_Tasks(void);

uint8_t SCH_Delete_Task(sTask* deleted_task);

void SCH_Go_To_Sleep(void);

void SCH_Report_Status(void);

#endif /* INC_SCHEDULER_H_ */

