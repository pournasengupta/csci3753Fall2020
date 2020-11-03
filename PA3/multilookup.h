//PROGRAMMING ASSIGNMENT 3 
//POURNA SENGUPTA
//MULTI-LOOKUP.H: PROGRAM HEADER 


#ifndef MULTILOOKUP_H
#define MULTILOOKUP_H

//Libraries
#include <stdio.h> 
#include <stdlib.h>

//Limits
#define MIN_RESOLVER 2
#define INPUTFS "%1024S"
#define MAX_RESOLVER 10 

struct timeVal{
    long *startTime; 
    long *endTime; 
}; 


void* requestThread(char*); 
void* resolvedThread(); 

#endif