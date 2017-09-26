//
// Created by rifatul on 9/23/17.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct page {
    unsigned long frame;
    unsigned long valid;

} pageType;


/*** This function converts pageNum to the frame in physical address and uses LRU for swap***/
int convertPageToFrame(unsigned long pageNum, unsigned long *frame);

/** This function create the page table and initialize it **/
pageType *createPageTable(unsigned long size);

/** Clean Up the virtual space and free up memory **/
int cleanUpVirtual();
