#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>
#include<stdlib.h>
#include <strings.h>
#include <limits.h>
#include<pthread.h>

int main(int argc , char* argv[]){
	int niceA;
	FILE *fptr;
   	fptr = fopen("niceValueA.txt","r"); 
   	fscanf(fptr,"%d", &niceA);
   	fclose(fptr); 
	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME,&start);
	struct sched_param param;
   	int pid_num = 0;
   	pid_t x = fork();
   	if(x==0){
   		int priority = niceA;
   		param.sched_priority = priority;
  //  		sched_setscheduler(pid_num, SCHED_OTHER, &param);
  //  		printf("priority value for SCHED_OTHER: %d\n",priority);
		// execl("/bin/bash" , "sh" , "bashScript1.sh", NULL); 
	}
	else{
		wait(NULL); 
		clock_gettime(CLOCK_REALTIME,&end);
    		double timeA = (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)*0.000000001;
		printf("time OTHER: %f\n",timeA);
		for(int i = 0 ; i<(int)timeA/20 ; i++){
			printf("|"); 
		}
		printf("\n");
		FILE *ptrA ;
		ptrA = fopen("timetaken_OTHER","a");
		fprintf(ptrA, "%f ", timeA);
		for(int i = 0 ; i< timeA/20 ; i++){
			fprintf(ptrA, "%s", "|");
		}
		fprintf(ptrA,"\n");
		fclose(ptrA); 
	}
	return 0;
}
