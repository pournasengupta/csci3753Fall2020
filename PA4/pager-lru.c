/*
 * File: pager-lru.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains an lru pageit
 *      implmentation.
 */

#include <stdio.h> 
#include <stdlib.h>

#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) { 
    
    /* This file contains the stub for an LRU pager */
    /* You may need to add/remove/modify any part of this file */

    /* Static vars */
    static int initialized = 0;
    static int tick = 1; // artificial time
    static int timestamps[MAXPROCESSES][MAXPROCPAGES];

    /* Local vars */
    int proctmp; /*current process*/
    int pagetmp; /*current page*/
    int pc; 
    int page; 
    int lru; 
    int lru_page;

    /* initialize static vars on first run */
    if(!initialized){
	for(proctmp = 0; proctmp < MAXPROCESSES; proctmp++){
	    if(q[proctmp].active){

        }
        for(pagetmp = 0; pagetmp < MAXPROCPAGES; pagetmp++){
		    timestamps[proctmp][pagetmp] = 0; 
	    }
	}
	initialized = 1;
    }
    
    /* TODO: Implement LRU Paging */
    /*fprintf(stderr, "pager-lru not yet implemented. Exiting...\n");
    exit(EXIT_FAILURE);*/

    /*LRU PAGING*/

    /*Loop through processes */
    for(proctmp =0; proctmp < MAXPROCESSES; ++proctmp){
        if(q[proctmp].active){
            pc = q[proctmp].pc; 
            page = pc/PAGESIZE; 
            timestamps[proctmp][page] = tick; 

            if(!q[proctmp].pages[page]){
                if(!pagein(proctmp,page)){
                    lru = tick; 
                    // if 
                    for(pagetmp = 0; pagetmp < MAXPROCPAGES; ++pagetmp){
                        if(timestamps[proctmp][pagetmp] < lru && q[proctmp].pages[pagetmp]){
                            lru_page = pagetmp; 
                            lru = timestamps[proctmp][pagetmp]; 
                        }
                    }
                    pageout(proctmp, lru_page); 
                }
            }
        }
    }

    /* advance time for next pageit iteration */
    tick++;
} 
