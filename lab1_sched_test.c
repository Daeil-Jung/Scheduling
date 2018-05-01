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

int main(int argc, char *argv[]){
	int menu = 0;
	queue presentQ;
	InitQueue(&presentQ);
	printf("select simulation scheduling that you want to see.\n");
	printf("1. FCFS  2. SJF  3. RR  4. MLFQ  5. Lottery  6.Exit\n");
	scanf("%d", &menu);
	while(menu!=6){
		switch(menu){
			case 1: FCFS(&presentQ);
				break;
			case 2: SJF(&presentQ);
				break;
			case 3: RR(&presentQ);
				break;
			case 4: MLFQ(&presentQ);
				break;
			case 5: Lotttery(&presentQ);
				break;
			default : printf("Plz put in value 1~6 :(");
		}
	}
	return 0;
}
