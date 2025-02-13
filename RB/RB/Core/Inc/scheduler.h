/*
 * scheduler.h
 *
 *  Created on: Nov 5, 2024
 *      Author: User
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
#define TICK 100
typedef struct{
	void (*pTask)(void);
	uint32_t	Delay;
	uint32_t	Period;
	uint8_t		RunMe; // so lan thuc hien 1 task

	uint32_t	TaskID;
}sTasks;

#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0
extern sTasks SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init(void);

// ~setTimer
void SCH_Add_Task ( void (*pFunction)(),
					uint32_t DELAY,
					uint32_t PERIOD);

// ~timerRun
void SCH_Update(void); // luon nam trong ngat timer

void SCH_Dispatch_Tasks(void); // luon nam trong while(1)

#endif /* INC_SCHEDULER_H_ */
