//
// Created by rifatul on 9/25/17.
//

#include <stdio.h>
#include <stdlib.h>


int getPageFaults();

int createPhysicalSpace(unsigned long physicalSize);

int freePhysical();

int updateFrame(unsigned long frame);

int getPhysicalSwap(unsigned long pagenum, unsigned long *pageSwapped, unsigned long *frame);
