/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32144204 
*	    Student name : Daeil-Jung
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm function'definition.
*
*/

#include <aio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <pthread.h>
#include <asm/unistd.h>

#include "lab1_sched_types.h"

/*
 * you need to implement FCFS, RR, SPN, SRT, HRRN, MLFQ scheduler. 
 */

void InitQueue(queue *q){
	q->front = q->rear = NULL;
	q->count = 0;
}

int IsEmpty(queue *q){
	return q->count == 0;
}

void Enqueue(queue *q, int data){
	node *now = (node *)malloc(sizeof(node));
	now->value = data;
	now->next = NULL;

	if(IsEmpty(q)){
		q->front = now;
	}
	else{
		q->rear->next = now;
	}
	q->rear = now;
	q->count++;
}

int Dequeue(queue *q){
	int re = 0;
	node *now;
	if(IsEmpty(q)){
		return re;
	}
	now = q->front;
	re = now->value;
	q->front = now->next;
	free(now);
	q->count--;
	return re;
}

void printQueue(queue *q, int a){
	printf("%c", (a+65));
	int time = 0;
	nptr now = q->front;
	for(time = 0;time<MAX_SERV_TIME;time++){
		if(now->value == a)
			printf(" O ");
		else
			printf(" X ");
		now = now->next;
	}
	printf("\n");
}

void FCFS(){
	int time = 0;
	int proc = 0;
	queue q;
	queue procQ;
	InitQueue(&q);
	InitQueue(&procQ);

	printf("You select FCFS scheduling.\n  ");
	for(time=0;time<MAX_SERV_TIME;time++){
		printf("%3d", time);
	}

	for(time=0;time<MAX_SERV_TIME;time++){
		for(proc = 0; proc < NUM_OF_PROC; proc++){
			if(arrivalTime[proc] == time){
				Enqueue(&q, proc);
			}
		}
		Enqueue(&procQ, (&q)->front->value);
		serviceTime[(&q)->front->value]--;
		if((serviceTime[(&q)->front->value]) == 0){
			Dequeue(&q);
		}
	}
	printf("\n");
	for(proc=0;proc<NUM_OF_PROC;proc++){
		printQueue(&procQ, proc);	
	}
}

void SJF(){
	int time = 0;
	int proc= 0;
	queue q;
	queue procQ;
	InitQueue(&q);
	InitQueue(&procQ);

	printf("You select SJF scheduling.\n  ");
	for(time=0;time<MAX_SERV_TIME;time++){
		printf("%3d", time);
	}
	for(time=0;time<MAX_SERV_TIME;){
		for(proc=0;proc<NUM_OF_PROC;proc++){
			if((arrivalTime[proc]<=time)&&(serviceTime[proc]!=0)){
				if(IsEmpty(&q))
					Enqueue(&q, proc);
				else if(serviceTime[(&q)->front->value]<serviceTime[proc]){
						Dequeue(&q);
						Enqueue(&q, proc);
				}
			}
		}
		while(serviceTime[(&q)->front->value]==0){
			Enqueue(&procQ, (&q)->front->value);
			serviceTime[(&q)->front->value]--;
			time++;
		}
		InitQueue(&q);
	}
	printf("\n");
	for(proc=0;proc<NUM_OF_PROC;proc++)
		printQueue(&procQ, proc);
}

void RR(){
	int time = 0;
	int proc = 0;
	int temp;
	queue q;
	queue procQ;
	InitQueue(&q);
	InitQueue(&procQ);

	printf("You select RR scheduling.\n  ");
	for(time=0;time<MAX_SERV_TIME;time++)
		printf("%3d", time);
	for(time=0;time<MAX_SERV_TIME;time++){
		for(proc=0;proc<NUM_OF_PROC;proc++){
			if(arrivalTime[proc]==time)
				Enqueue(&q, proc);
		}
		if((time!=0)&&(serviceTime[temp]!=0))
			Enqueue(&q, temp);
		Enqueue(&procQ, (&q)->front->value);
		serviceTime[(&q)->front->value]--;
		temp = Dequeue(&q);
	}
	printf("\n");
	for(proc=0;proc<NUM_OF_PROC;proc++)
		printQueue(&procQ, proc);
}
/*
void MLFQ(){
	int time = 0;
	int proc = 0;
	queue q;
	queue procQ[QUEUE_LEVEL];
	int i;
	for(i=0;i<QUEUE_LEVEL;i++)
		InitQueue(&procQ[i]);
	
	printf("You select MLFQ scheduling.\n  ");
	for(time=0;time<MAX_SERV_TIME;time++)
		printf("%3d", time);
	for(time=0;time<MAX_SERV_TIME;time++)
		for(proc=0;proc<NUM_OF_PROC;proc++){
			if(arrivalTime[proc]==time)
				Enqueue(&procQ[0],proc);


}

void Lottery(){
	
}

*/
