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

#define QUEUE_LEVEL 4
#define TIME_QUANT 1
#define NUM_OF_PROC 5
#define MAX_SERV_TIME 20

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
void Enqueue(queue *q, int data);
int Dequeue(queue *q);
void printQueue(queue *q, int a);

int arrivalTime[NUM_OF_PROC];
int serviceTime[NUM_OF_PROC];
int tickets[NUM_OF_PROC];

void FCFS();
void SJF();
void RR();/*
void MLFQ();

void Lottery();
*/
/*
 * You need to Declare functions in  here
 */


#endif /* LAB1_HEADER_H*/



