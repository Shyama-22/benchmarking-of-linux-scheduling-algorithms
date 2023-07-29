#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>
#include<stdlib.h>
#include <strings.h>
#include <limits.h>
#include<pthread.h>

int main(int argc , char* argv[]){
	int niceC;
	FILE *fptr;
   	fptr = fopen("niceValueC.txt","r"); 
   	fscanf(fptr,"%d", &niceC);
   	fclose(fptr); 
	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME,&start);
	struct sched_param param;
   	int pid_num = 0;
   	pid_t x = fork();
   	if(x==0){
   		int priority= niceC; 
		param.sched_priority = priority;
		// sched_setscheduler(pid_num, SCHED_FIFO, &param); 
  //  		printf("priority value for SCHED_FIFO: %d\n",priority);
		// execl("/bin/bash" , "sh" , "bashScript3.sh", NULL); 
	}
	else{
		wait(NULL); 
		
		clock_gettime(CLOCK_REALTIME,&end);
    	double timeA = (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)*0.000000001;
		printf("time FIFO: %f\n",timeA);
		for(int i = 0 ; i<(int)timeA/20 ; i++){
			printf("|"); 
		}
		printf("\n");
		FILE *ptrA ;
		ptrA = fopen("timetaken_FIFO","a");
		fprintf(ptrA, "%f", timeA);
		for(int i = 0 ; i< timeA/20 ; i++){
			fprintf(ptrA, "%s", "|");
		}
		fprintf(ptrA,"\n");
		fclose(ptrA); 

	}
	return 0;
}
