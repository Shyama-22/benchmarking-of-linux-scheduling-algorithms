#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>
#include<stdlib.h>
#include <strings.h>
#include <limits.h>
#include<pthread.h>
#include<sys/wait.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sched.h>
#include<math.h>
#include<time.h>

double timeA ; 
double timeB ; 
double timeC ; 
pid_t x;
pid_t y;
pid_t z;
int flagA = 0; 
int flagB = 0;
int flagC = 0;
int main(){
	
	FILE *ptrA ;
	ptrA = fopen("timetaken_RR","w");
	fclose(ptrA); 
	FILE *ptrB ;
	ptrB = fopen("timetaken_FIFO","w");
	fclose(ptrB); 
	FILE *ptrC ;
	ptrA = fopen("timetaken_OTHER","w");
	fclose(ptrC); 
	int niceA_arr[6] = {0,0,0,0,0}; 
	int niceB_arr[6] = {1,20,79,90,1}; 
	int niceC_arr[6] = {40,89,3,4,80}; 
	int start; 
	for(int o = 0 ; o<6 ; o++){
		
		int in; 
		int status;

		int niceA = niceA_arr[o]; 
		FILE *ptrA = fopen("fileopen","mode");
		ptrA = fopen("niceValueA.txt","w");
		fprintf(ptrA, "%d", niceA);
		fclose(ptrA); 
		



		int niceB = niceB_arr[o]; 
		FILE *ptrB = fopen("fileopen","mode");
		ptrB = fopen("niceValueB.txt","w");
		fprintf(ptrB, "%d", niceB);
		fclose(ptrB); 
		



		int niceC = niceC_arr[o]; 
		FILE *ptrC = fopen("fileopen","mode");
		ptrC = fopen("niceValueC.txt","w");
		fprintf(ptrC, "%d", niceC);
		fclose(ptrC); 
		


		double startTime = clock(); 
		x = fork();
		if(x == 0){
			char *args[] = {NULL , NULL , NULL , NULL}; 
			execv("./bashA", args);
		}
		else{
			y = fork();
			if(y == 0){
				char *args[] = {NULL , NULL , NULL , NULL}; 
				execv("./bashB", args);
			}
			else{
				z = fork();
				if(z==0){
					char *args[] = {NULL , NULL , NULL , NULL}; 
					execv("./bashC", args);
				}
				else{
					while(((x = waitpid(x, &status, WNOHANG))!=-1 || (y = waitpid(y, &status, WNOHANG))!=-1) || ((z = waitpid(z, &status, WNOHANG))!=-1)){
						wait(NULL); 
					}					
				}
			}
		}
	printf("parent reached :)\n" );
	}
	return 0;
}










