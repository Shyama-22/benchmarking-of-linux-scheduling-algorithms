#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sched.h>
#include<math.h>
#include<time.h>

pthread_t a;
pthread_t b;
pthread_t c;

int priorityA=0; //other
int priorityB=1; //RR
int priorityC=1; //FIFO

long iniA; 
long iniB; 
long iniC; 

long finA; 
long finB; 
long finC;

double timeA , timeB , timeC;

void print_histogram(double execution_time_A , double execution_time_B , double execution_time_C){

    printf("\nHISTOGRAM \n");
    printf("Standard Linux Scheduling * priority:%d\n" , priorityA);
    for(int i = 0 ; i<(execution_time_A*10); i++){
        printf("|");
    }
    printf("\n");
    printf("Round Robin Scheduling: * priority:%d\n" , priorityB);
    for(int i = 0 ; i<(execution_time_B*10) ; i++){
        printf("|");
    }
    printf("\n");
    printf("First-In-First-Out Scheduling * priority:%d\n" , priorityC);
    for(int i = 0 ; i<(execution_time_C*10) ; i++){
        printf("|");
    }
    printf("\n\n");
}


void* countA(void* args){

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME,&start);
    struct sched_param paramA;
    paramA.sched_priority = priorityA; 
    printf("%d" , pthread_setschedparam(a, SCHED_OTHER, &paramA));
    for(long int i = 1 ; i<4294967296 ; i++){
        continue; 
    }
    clock_gettime(CLOCK_REALTIME,&end);
    timeA = (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)*0.000000001;
    return NULL ; 
}

void* countB(void* args){

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME,&start);
    struct sched_param paramB;
    paramB.sched_priority = priorityB;
    printf("%d" , pthread_setschedparam(b, SCHED_RR, &paramB));
    for(long int i = 1 ; i<4294967296 ; i++){
        continue; 
    }
    clock_gettime(CLOCK_REALTIME,&end);
    timeB = (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)*0.000000001;
    return NULL ; 
}

void* countC(void* args){

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME,&start);
    struct sched_param paramC;
    paramC.sched_priority = priorityC; 
    printf("%d" , pthread_setschedparam(c, SCHED_FIFO, &paramC));
    for(long int i = 1 ; i<4294967296 ; i++){
        continue; 
    }
    clock_gettime(CLOCK_REALTIME,&end);
    timeC = (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)*0.000000001;
    return NULL ;
}

int main(){
    
        int priorityAArray[10] = {0 , 0 , 0 , 0 , 0  , 0 , 0 , 0 , 0 , 0} ;
        int priorityBArray[10] = {1 , 1 , 1 , 30 , 60 , 98  , 1 , 15 , 18 , 1} ;
        int priorityCArray[10] = {10 , 30 , 99 , 1  , 1 , 1 , 40 , 13  , 19 , 9} ;
        int ptr = 0 ; 
        for(int ptr =  0;  ptr<10 ; ptr++ ){

        priorityA = priorityAArray[ptr];
        priorityB = priorityBArray[ptr];
        priorityC = priorityCArray[ptr];
        pthread_create(&a, NULL, &countA, NULL);
        pthread_create(&b, NULL, &countB, NULL);  
        pthread_create(&c, NULL, &countC, NULL);

        pthread_join(a, NULL); 
        pthread_join(b, NULL);
        pthread_join(c, NULL);

        printf("OTHER: %lf\n", (double)(timeA));
        printf("RR: %lf\n", (double)(timeB));
        printf("FIFO: %lf\n", (double)(timeC));

        print_histogram(timeA,timeB ,timeC); 
        printf("------------------------------\n");
    }


	return 0; 
}


