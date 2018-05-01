/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 
*	    Student name : 
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
	queue->count = 0;
}

int IsEmpty(queue *q){
	return queue->count == 0;
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
	re = now->data;
	q->front = now->next;
	free(now);
	q->count--;
	return re;
}

void printQueue(queue *q, int a){
	printf("%c", (a+65));
	int time = 0;
	nptr now = q->front;
	for(time = 0;time<maxservtime;time++){
		if(now->value == a)
			printf("  O");
		else
			printf("  X");
		now = now->next;
	}
}

void FCFS(queue *q){
	int time = 0;
	int proc = 0;

	printf("You select FCFS scheduling.\n");
	for(time=0;time<maxservtime;time++){
		printf("  %3d", time);
	}

	queue procQ;
	InitQueue(&procQ);
	for(time=0;time<maxservtime;time++){
		for(proc = 0; proc < num_of_proc; proc++){
			if(arrivalTime[proc] == time){
				Enqueue(q, proc);
			}
		}
		InitQueue(&procQ, q->front->value);
		servicetime[q->front->value];
		if((q->front->value) == 0){
			Dequeue(q);
		}
	}
	printf("\n");
	for(proc=0;proc<num_of_proc;proc++){
		printQueue(&procQ, proc);	
	}
}
