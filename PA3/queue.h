//PROGRAMMING ASSIGNMENT 3 
//POURNA SENGUPTA
//QUEUE.H: FIFO QUEUE HEADER

#ifndef QUEUE_H
#define QUEUE_H

//Libraries
#include <stdio.h> 
#include <stdlib.h>

//Limits
#define QUEUEMAX 20
#define QUEUE_FALSE -1 
#define QUEUE_TRUE 0 

typedef struct queueN {
    void* newNode; 
}queue_node; 

typedef struct queueF {
    queue_node* array; 
    int first; 
    int last; 
    int maxSize; 
}queue; 

//initialize new queue
//Input: Queue, Size  
int queue_new(queue*, int); 

//check for empty queue 
//Input: Queue
int isEmpty(queue*); 

//check for full queue 
//Input: Queue
int isFull(queue*); 

//Return queue elements
//Input: Queue
void* elements(queue*);

//Add load to end of queue 
//Input: Queue, Payload 
int pushQ(queue*, void*); 

//Clean queue memory 
//Input: Queue
void cleanQ(queue*); 

#endif