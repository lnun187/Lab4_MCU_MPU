/*
 * scheduler.h
 *
 *  Created on: Nov 13, 2024
 *      Author: Admin
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#include "main.h"
#include "test_sche.h"
#define SCH_MAX_TASKS 3
#define NO_TASK_ID 0
#define RETURN_ERROR 1
#define RETURN_NORMAL 0
void SCH_Init (void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD);
unsigned char SCH_Delete_Task();

#endif /* INC_SCHEDULER_H_ */