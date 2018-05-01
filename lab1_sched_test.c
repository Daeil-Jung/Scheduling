/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 
*	    Student name : 
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm test code.
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
 * you need to implement scheduler simlator test code.
 *
 */

arrivalTime[num_of_proc] = {0, 2, 4, 6, 8};
serviceTime[num_of_proc] = {3, 6, 4, 5, 2};
tickets[num_of_proc] = {3, 5, 4, 6, 2};

int main(int argc, char *argv[]){
	int menu = 0;
	queue presentQ;
	InitQueue(&presentQ);
	printf("select simulation scheduling that you want to see.\n");
	printf("1. FCFS  2. SJF  3. RR  4. MLFQ  5. Lottery  6.Exit\n");
	scanf("%d", &menu);

	switch(menu){
		case 1: FCFS(&presentQ);
			break;
		case 2: SJF(&presentQ);
			break;
		case 3: RR(&presentQ);
			break;/*
		case 4: MLFQ(&presentQ);
			break;
		case 5: Lotttery(&presentQ);
			break;*/
		default : printf("Plz put in value 1~6 :(");
	}
	return 0;
}
