/*
 * scheduler.c
 *
 *  Created on: Nov 13, 2024
 *      Author: Admin
 */

#include "scheduler.h"

typedef struct sTask{
	// Pointer to the task (must be a ’ void (void) ’ function )
	void (*pTask)(void);
	// Delay (tick s) until the function w ill ( next ) be run
	int Delay;
	// Interval (ticks) between subsequent runs.
	int Period;
	// Incremented (by scheduler) when task is due to execute
	int RunMe;
	// This is a hint to solve the question below.
	int TaskID;
	struct sTask* next;
} sTask;

typedef struct	{
	sTask* head;
} sTaskList;

sTaskList taskList;
// MUST BE ADJUSTED FOR EACH NEW PROJECT

//sTask SCH_tasks_G[SCH_MAX_TASKS];
void SCH_Init(void) {
	sTask* temp;
	for (; taskList.head;) {
		temp = taskList.head;
		taskList.head = (taskList.head)->next;
		free(temp);
	}
	// Reset the global error variable
	// − SCH_Delete_Task () w ill generate an error code ,
	// ( because the task array i s empty)
	//Timer_init () ;
	//Watchdog_init () ;
}
void SCH_Update(void) {
	// NOTE: calculations are in *TICKS* ( not milliseconds )
	taskList.head->Delay--;
}
void SCH_Dispatch_Tasks(void) {
	sTask *temp = taskList.head;
// Dispatches ( runs ) the next task ( i f one i s ready )
	while(temp){
		if (temp->Delay == 0) {
			(*(temp->pTask))(); // Run the task
			temp->RunMe = 0; // Reset / reduce RunMe fl ag
// Periodic tasks w ill automatically run again
// − i f thi s i s a ’one shot ’ task , remove i t from the array
			SCH_Delete_Task();
			if (temp->Period > 0) {
				SCH_Add_Task(temp->pTask, temp->Period, temp->Period);
			}
			free(temp);
			temp = taskList.head;
		} else break;
	}
// Report system status
// The scheduler enters idle mode at thi s point
//SCH_Go_To_Sleep() ;
}
void SCH_Add_Task(void function(), unsigned int DELAY, unsigned int PERIOD) {
	sTask* temp;
	sTask* prev;
	sTask* i = taskList.head;
	temp = (sTask*) malloc(sizeof(sTask));
	temp->pTask = function;
	temp->Delay = DELAY;
	temp->Period = PERIOD;
	temp->RunMe = 0;
	temp->next = NULL;
	int count = 0;
	while(i){
		count += i->Delay;
			if(temp->Delay <= count) break;
			prev = i;
			i = i->next;
		}
	if(!taskList.head) taskList.head = temp;
	else if(!i) {
		temp->Delay -= count;
		prev->next = temp;
	} else if(i == taskList.head){
		i->Delay -= temp->Delay;
		temp->next = i;
		taskList.head = temp;
	} else{
		temp->Delay -= (count - i->Delay);
		prev->next = temp;
		i->Delay -= temp->Delay;
		temp->next = i;
	}
	// F i r st find a gap in the array ( i f there i s one)
	// Have we reached the end of the l i s t ?
	// I f we ’ re here , there i s a space in the task array

	// return position of task ( to allow l at e r deletion )
}
unsigned char SCH_Delete_Task() {
	unsigned char Return_code;
	if(taskList.head == 0) Return_code = RETURN_ERROR;
	else {
		Return_code = RETURN_NORMAL;
		taskList.head = taskList.head->next;
	}

	return Return_code; // return status
}
