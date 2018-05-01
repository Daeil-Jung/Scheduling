/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32144204
*	    Student name : Daeil-Jung
*
*   lab1_sched_types.h :
*       - lab1 header file.
*       - must contains scueduler algorithm function's declations.
*
*/

#ifndef _LAB1_HEADER_H
#define _LAB1_HEADER_H

int queueLevel 4;
int timeQ 1;
int num_of_proc 5;
int maxservtime 20;

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

void InitQueue(queue *q);
int IsEmpty(queue *q);
void Enqueue(queue *q);
int Dequeue(queue *q);
void printQueue(queue *q, int a);

int arrivalTime[num_of_proc] = {0, 2, 4, 6, 8};
int serviceTime[num_of_proc] = {3, 6, 4, 5, 2};

void FCFS(queue *q);
void SJF(queue *q);
void RR(queue *q);
void MLFQ(queue *q);
void Lottery(queue *q);

/*
 * You need to Declare functions in  here
 */


#endif /* LAB1_HEADER_H*/



