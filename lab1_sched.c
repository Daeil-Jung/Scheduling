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

typedef struct _node{
	int value;
	struct _node* next;
}node;

typedef node* nptr;

typedef struct _queue{
	int count;
	nptr front;
	nptr rear;
}queue;

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

void FCFS(){
	
}
