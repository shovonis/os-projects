//
// Created by rifatul on 9/25/17.
//

#include <stdio.h>
#include <stdlib.h>
#include "phypages.h"

unsigned long *physicalTable = NULL;
unsigned long *reverse = NULL;
unsigned long location = 0;
unsigned long physicalSz;
unsigned long full = 0;
int pageFaults = 0;

//Create the physical address space
int createPhysicalSpace(unsigned long physicalSize) {
    unsigned long i;
    physicalTable = (unsigned long *) malloc(sizeof(unsigned long) * physicalSize);
    reverse = (unsigned long *) malloc(sizeof(unsigned long) * physicalSize);

    if (physicalTable == NULL || reverse == NULL) {
        perror("[ERROR]Creation error in malloc ");
        return -1;
    }

    for (i = 0; i < physicalSize; i++) {
        physicalTable[i] = 0;
        reverse[i] = 0;
    }
    physicalSz = physicalSize;

    return 0;
}

//** If no need to swap then allocate the frame
int updateFrame(unsigned long frame) {
    if (physicalTable == NULL) {
        return -1;
    }
    physicalTable[frame] = location++;
    return 0;
}

// clean up all the memory
int freePhysical() {
    free(physicalTable);
    free(reverse);

    return 0;
}

int getPhysicalSwap(unsigned long pagenum, unsigned long *pageSwapped, unsigned long *frame) {
    unsigned long i, min = physicalTable[1], minIndex = 1;
    pageFaults++;

    if (physicalTable == NULL) {
        return -1;
    }

    if (location == 0) {
        physicalTable[1] = location++;
        reverse[1] = pagenum;
        *frame = 1;
        return 0;
    }

    for (i = 1; i < physicalSz; i++) {

        if (physicalTable[i] == 0 && i != 1) {
            physicalTable[i] = location++;
            reverse[i] = pagenum;
            *frame = i;
            return 0;
        } else if (min > physicalTable[i]) {
            min = physicalTable[i];
            minIndex = i;

        }
    }

    *pageSwapped = reverse[minIndex];

    physicalTable[minIndex] = location++;     //LRU frame the newest spot
    reverse[minIndex] = pagenum;
    *frame = minIndex;
    return 0;

}

int getPageFaults() {
    return pageFaults;
}
