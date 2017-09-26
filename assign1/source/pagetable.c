//
// Created by rifatul on 9/23/17.
//

#include <stdio.h>
#include <stdlib.h>
#include "pagetable.h"
#include "phypages.h"

pageType *page = NULL;



int convertPageToFrame(unsigned long pageNum, unsigned long *frame) {
    unsigned long tempFrame, pageSwapped; //If swap

    int error = 0;
    if (page[pageNum].valid == 0) { // If valid bit is zero then we need get swap from physical.
        error = getPhysicalSwap(pageNum, &pageSwapped, &tempFrame);
        if (error == -1) { // Make sure the getPhysicalSwap worked perfectly
            return -1;
        }
        page[pageSwapped].valid = 0;
        page[pageNum].frame = tempFrame;
        page[pageNum].valid = 1; //Reusing the frame so set valid bit to 1 again
        *frame = tempFrame;
        return 0;
    } else {                  // The page is valid and
        updateFrame(page[pageNum].frame);
        *frame = page[pageNum].frame;
        return 0;
    }
}

// Create and initlize the page table
pageType *createPageTable(unsigned long size) {
    page = (pageType *) malloc(sizeof(pageType) * size);

    if (page == NULL) {
        return NULL;
    }

    for (unsigned long i = 0; i < size; i++) {
        page[i].frame = 0;
        page[i].valid = 0;
    }

    return page;
}

//Free up memory
int cleanUpVirtual() {
    free(page);
    return 0;
}
