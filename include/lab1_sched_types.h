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

#define queueLevel 4
#define timeQ 1
#define num_of_proc 5
#define maxservtime 20

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

int arrivalTime[num_of_proc];
int serviceTime[num_of_proc];
int tickets[num_of_proc];

void FCFS(queue *q);
void SJF(queue *q);
void RR(queue *q);
/*
void MLFQ(queue *q);
void Lottery(queue *q);
*/
/*
 * You need to Declare functions in  here
 */


#endif /* LAB1_HEADER_H*/



