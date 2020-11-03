//PROGRAMMING ASSIGNMENT 3 
//POURNA SENGUPTA
//MULTI-LOOKUP.C: PROGRAM 

//Libraries
//C Standard Library
#include <stdlib.h>
//C String Library 
#include <string.h>
//Linux pthread Library 
#include <pthread.h>
//Linux Semaphore Library--
//Standard I/O Library
#include <stdio.h>
//for runtime
#include <sys/time.h>
#include <time.h>
//for sleep()
#include <unistd.h>


//Header Files 
#include "queue.h"
#include "util.h"
#include "multilookup.h"


//Set queue and outfile mutexes 
//Queue Mutex
pthread_mutex_t mutexQ; 
//Results Mutex
pthread_mutex_t mutexR; 

//finding processing time of system 

//declare variables and set initial value 
//Time Variables 
int t1 = 0; 
int t2 = 0; 
//Requester 
int reqTrue = 1; 
int reqFalse = 0; 
//File Processes Completed
int fin = 0; 


//define queue 
queue q; 
//Files to write to 
FILE* serviced; 
FILE* results;
FILE* performance; 

//FUNCTIONS 

//requester function 
//Read in file line by line
//Place hostname into shared array 
//Log hostname into serviced files 
void* requestThread(char *inFile){
    FILE* input = NULL; 
    char hostname[1025]; 
    //char error[1025]; 

    //read file into input 
    input = fopen(inFile, "r"); 
    if(input == NULL){
        //print error 
        printf("Bogus Input File Path"); 
    }

    //scan file for IP and Hostname 
    while(fscanf(input, "%s", hostname) > 0){
        //strdup() return point to new string
        //new string is duplicate of hostname 
        char* host = strdup(hostname); 
        pthread_mutex_lock(&mutexQ);

        //when queue is full 
        while(isFull(&q)){
            pthread_mutex_unlock(&mutexQ); 
            usleep(rand() % 100); 
            pthread_mutex_lock(&mutexQ); 
        }

        pushQ(&q, (void*) host); 
        pthread_mutex_unlock(&mutexQ); 
    }

    fin++; 
    reqFalse--; 
    return 0; 
}

//resolver function 
//remove hostname from shared array 
//find IP for hostname 
//write results to results.txt
void* resolveThread(){
    //Optional Limit 
    char *hostname; 
    char hostIP = gethostid();

    //Check if request has occurred 
    //Check if queue is empty 
    while(reqTrue || !isEmpty(&q)){
        pthread_mutex_lock(&mutexQ); 
        hostname = elements(&q); 

        pthread_mutex_unlock(&mutexQ);

        if(dnslookup(hostname, &hostIP, sizeof(hostIP)) == UTIL_FAILURE){
            //print error
            printf("Bogus Hostname"); 
            //copy string 
            results = fopen(hostname, "w"); 
        } 
        //print formatted hostname and IP 
        fprintf(results, "%s, %s\n", hostname, &hostIP); 
        pthread_mutex_unlock(&mutexQ); 
    }
    pthread_exit(NULL); 
    return NULL; 
}

int main(int argc, char* argv[]){
    struct timeval *startTime=NULL, *endTime=NULL; 
    //get time of day 
    //start 
    gettimeofday(startTime, NULL); 

    int numFiles = argc - 5; 
    //convert into an int
    char *reqString = argv[(argc - numFiles - 4)];
    int reqThread = atoi(reqString);
    char *resString = argv[(argc - numFiles - 3)];
    int resThread = atoi(resString); 
    char req[]= "Number of Requester Threads is "; 
    performance = fopen(strcat(req, reqString), "w"); 
    char res[] = "Number of Resolver Threads is "; 
    performance = fopen(strcat(res, resString), "w"); 

    if(!results){
        printf("Bogus Output File Path");
        printf("%s", (argv[argc-1])); 
        return EXIT_FAILURE;  
    }

    if(reqThread > numFiles){
        printf("Error: More requester threads than input files\n"); 
        reqThread = numFiles; 
    }

    pthread_t requested[reqThread]; 
    pthread_t resolved[resThread]; 

    queue_new(&q, 0); 

    pthread_mutex_init(&mutexQ, NULL); 
    pthread_mutex_init(&mutexR, NULL);

    for(int i = 0; i < numFiles; i++){
        if(reqFalse >= reqThread){
            sleep(1); 
        }
        reqFalse++;
        fprintf(serviced, "Thread %d serviced %s files\n", reqFalse, argv[i+5]); 
        pthread_create(&(requested[i]), NULL, requestThread(argv[i+5]), (void*) argv[i+5]); 
    } 

    for(int j = 0; j < resThread; j++){
        pthread_create(&(resolved[j]), NULL, resolveThread, NULL); 
    }

    for(int k = 0; k < reqThread; k++){
        pthread_join(requested[k], NULL); 
    }

    reqTrue = 0; 

    for(int l = 0; l < resThread; l++){
        pthread_join(resolved[l], NULL); 
    }

    fclose(results); 
    gettimeofday(endTime, NULL); 

    //Program Runtime 
    //convert start and end time into seconds and nanoseconds
    //calculate run time 
    //long calcSec = (endTime.tv_sec - startTime.tv_sec); 
    //long calcMicro = ((calcSec * 1000000) + endTime.tv_usec) - (startTime.tv_usec); 
    //printf("Time to completed: %d seconds & %d microseconds\n", calcSec, calcMicro); 
    printf("%ld", (endTime - startTime)); 

    cleanQ(&q); 
    pthread_mutex_destroy(&mutexQ); 
    pthread_mutex_destroy(&mutexR); 
    return 0; 
}