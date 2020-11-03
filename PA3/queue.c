//PROGRAMMING ASSIGNMENT 3 
//POURNA SENGUPTA
//QUEUE.C: FIFO QUEUE PROGRAM

//Libraries 
#include <stdlib.h>
//Standard I/O Library
#include <stdio.h>

//Header File 
#include "queue.h"

//initialize new queue
//Input: Queue, Size  
//Return: Queue 
int queue_new(queue* q, int n){

    //set queue maxSize 
    //if user inputs size 
    if(n > 0){
        q -> maxSize = n; 
    }
    //else default size 
    else{
        q -> maxSize = QUEUEMAX; 
    }

    //Allocate Memory for new array using malloc 
    q -> array = malloc(sizeof(queue_node) * (q -> maxSize)); 
    if(!(q -> array)){
        printf("Error"); 
        return QUEUE_FALSE; 
    }

    for(int i = 0; i < q -> maxSize; i++){
        q -> array[i].newNode = NULL; 
    }

    //Queue Buffer Values 
    q -> first = 0; 
    q -> last = 0; 

    //Return Queue MaxSize 
    return (q -> maxSize); 
} 

//check for empty queue 
//Input: Queue
//Return: Int (0 or 1)
int isEmpty(queue* q){
    //check if first and last are equal 
    //check if value loaded in to first is NULL
    if((q -> first == q -> last) && (q -> array[q -> first].newNode == NULL)){
        //return 1
        //queue is empty 
        return 1; 
    }
    else{
        //return 0
        //queue is not empty 
        return 0; 
    }
} 

//check for full queue 
//Input: Queue
//Return: Int (0 or 1)
int isFull(queue* q){
    //check if first and last are equal 
    //check if value loaded in to first is not NULL
    if((q -> first == q -> last) && (q -> array[q -> first].newNode != NULL)){
        //return 1
        //queue is full 
        return 1; 
    }
    else{
        //return 0
        //queue is not full 
        return 0; 
    }
} 

//Return queue elements
//Input: Queue
//Return: NULL if empty, payload
void* elements(queue* q){
    //Define Variable 
    void* q_nodes; 

    //Check for Empty Queue 
    if(isEmpty(q)){
        //Return Null for empty queue 
        return NULL; 
    }

    //Find elements of queue 
    q_nodes = q -> array[q -> first].newNode;  
    //Set element to NULL
    q -> array[q -> first].newNode = NULL; 
    //Move first node left by 1
    q -> first = ((q -> first + 1) % q -> maxSize); 

    //return the elements 
    return q_nodes; 
}

//Add load to end of queue 
//Input: Queue, Payload 
//Return: QUEUE_TRUE or QUEUE_FALSE
int pushQ(queue* q, void* p){
    //Check for Full Queue 
    if(isFull(q)){
        //No more elements can be added 
        return QUEUE_FALSE; 
    }

    //Set newNode to input variable p
    q -> array[q -> last].newNode = p; 
    //Move last node right by 1
    q -> last = ((q -> last + 1) % q -> maxSize); 

    //Return Success of Node Addition 
    return QUEUE_TRUE; 
} 

//Clean queue memory 
//Input: Queue
//Return: None
void cleanQ(queue* q){
    //if queue is not empty 
    while(!isEmpty(q)){
        //call elements function 
        elements(q); 
    }

    //free up array 
    free(q -> array); 

}