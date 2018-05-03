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

	printf("You select FCFS scheduling.\n");
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
	int arrivedQ[NUM_OF_PROC + 1];
	int minservtime = 0;
	int minservQ;
	queue q;
	InitQueue(&q);

	printf("You select SJF scheduling.\n");
	for(time=0;time<MAX_SERV_TIME;time++){
		printf("%3d", time);
	}
	for(time=0;time<MAX_SERV_TIME;){
		arrivedQ[0] = 0;
		for(proc=0;proc<NUM_OF_PROC;proc++){
			if ((arrivalTime[proc] <= time) && (serviceTime[proc] != 0)) {
				arrivedQ[0]++;
				arrivedQ[(arrivedQ[0])] = proc;
			}
		}
		minservtime = serviceTime[(arrivedQ[1])];
		minservQ = arrivedQ[1];
		for (proc = 2; proc <= arrivedQ[0]; proc++) { //in this case, proc has no means.
			if (minservtime > serviceTime[(arrivedQ[proc])]) {
				minservtime = serviceTime[(arrivedQ[proc])];
				minservQ = arrivedQ[proc];
			}
		}
		for (proc = 0; proc < minservtime; proc++) { //in this case, proc has no means.
			Enqueue(&q, minservQ);
			serviceTime[minservQ]--;
			time++;
		}
	}
	printf("\n");
	for(proc=0;proc<NUM_OF_PROC;proc++)
		printQueue(&q, proc);
}

void RR(){
	int time = 0;
	int proc = 0;
	int temp = 0;
	int exectime = 0;
	queue q;
	queue procQ;
	InitQueue(&q);
	InitQueue(&procQ);

	printf("You select RR scheduling.\n");
	printf("Time quantum is %d.\n", TIME_QUANT);
	for(time=0;time<MAX_SERV_TIME;time++)
		printf("%3d", time);
	for(time=0;time<MAX_SERV_TIME;time++){
		for(proc=0;proc<NUM_OF_PROC;proc++){
			if(arrivalTime[proc]==time)
				Enqueue(&q, proc);
		}
		if (((time != 0) && (serviceTime[temp] != 0)) && (exectime == TIME_QUANT)) {
			Enqueue(&q, temp);
			exectime = 0;
		}
		else if (serviceTime[temp] == 0) {
			exectime = 0;
			serviceTime[temp] = -1;
		}
		Enqueue(&procQ, (&q)->front->value);
		serviceTime[(&q)->front->value]--;
		exectime++;
		if((exectime == TIME_QUANT)||(serviceTime[(&q)->front->value]))
			temp = Dequeue(&q);
	}
	printf("\n");
	for(proc=0;proc<NUM_OF_PROC;proc++)
		printQueue(&procQ, proc);
}

void MLFQ(){
	int time = 0;
	int proc = 0;
	int temp = 0;
	int l = 0;
	int exectime = 0;
	queue q;
	queue procQ[QUEUE_LEVEL];
	int i;
	for(i=0;i<QUEUE_LEVEL;i++)
		InitQueue(&procQ[i]);
	InitQueue(&q);

	printf("You select MLFQ scheduling.\n");
	printf("Time quantum is %d. Queue leveil is %d.\n", TIME_QUANT, QUEUE_LEVEL);
	for(time=0;time<MAX_SERV_TIME;time++)
		printf("%3d", time);
	for(time=0;time<MAX_SERV_TIME;time++){
		for (proc = 0; proc < NUM_OF_PROC; proc++) {
			if (arrivalTime[proc] == time)
				Enqueue(&procQ[0], proc);
		}
		for (l = 0; l < QUEUE_LEVEL; l++) {
			if ((&procQ[l])->count != 0) {
				Enqueue(&q, (&procQ[l])->front->value);
				exectime++;
				serviceTime[(&procQ[l])->front->value]--;
				if ((serviceTime[(&procQ[l])->front->value]) == 0) {
					Dequeue(&procQ[l]);
					exectime = 0;
				}
				else if (exectime==TIME_QUANT) {
					temp = Dequeue(&procQ[l]);
					if (l < (QUEUE_LEVEL - 1))
						Enqueue(&procQ[l + 1], temp);
					else
						Enqueue(&procQ[l], temp);
					exectime = 0;
				}
				break;
			}
		}
	}
	printf("\n");
	for (proc = 0; proc<NUM_OF_PROC; proc++)
		printQueue(&q, proc);
}

void Lottery(){
	int time = 0;
	int proc = 0;
	int sum = 0;
	int temp = 0;
	queue q;
	queue procQ;
	queue ticketQ;
	InitQueue(&q);
	InitQueue(&procQ);
	InitQueue(&ticketQ);
	srand(time(NULL));

	printf("You select Lottery scheduling.\n");
	for (time = 0; time<MAX_SERV_TIME; time++)
		printf("%3d", time);
	for (time = 0; time < MAX_SERV_TIME; time++) {
		for (proc = 0; proc < NUM_OF_PROC; proc++)
			if (arrivalTime[proc] == time) {
				Enqueue(&procQ, proc);
				Enqueue(&ticketQ, tickets[proc]);
				sum += tickets[proc];
			}
		temp = rand() % sum;
		while (temp < (&ticketQ)->front->value) {
			proc = Dequeue(&procQ);
			Enqueue(&procQ, proc);
			proc = Dequeue(&ticketQ);
			Enqueue(&ticketQ, proc);
			temp = temp - ((&ticketQ)->front->value);
		}
		Enqueue(&q, (&procQ)->front->value);
		serviceTime[(&procQ)->front->value]--;
		if (serviceTime[(&procQ)->front->value] == 0) {
			proc = Dequeue(&procQ);
			Dequeue(&ticketQ);
			sum -= tickets[proc];
		}
	}
}
