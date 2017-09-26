//
// Created by rifatul on 9/26/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <math.h>
#include "phypages.h"
#include "pagetable.h"

int main(int argc, char *argv[]) {

    //Given Page Table information//
    unsigned long offsetBit;
    unsigned long virtualAddress;
    int fileInput;
    int fileOutput;
    int

    unsigned long offset;
    unsigned long frame;
    unsigned long physicalAddress;

    //Check input params
    if (argc != 5) {
        fprintf(stderr, "Invalid Params. The prams should be in format:  BytesOfPage SizeOfVirtualMemory SizeOfPhysicalMemory SequenceFile %s \n", argv[0]);
        exit(2);
    }

    unsigned long pages = (unsigned long)atoi(argv[2])/atoi(argv[1]);
    unsigned long frames = (unsigned long)atoi(argv[3])/atoi(argv[1]);
    unsigned long pagesize = (unsigned long)ceil(log2(atoi(argv[1])));

    //Try to open the output file
    fileInput = open(argv[1], O_RDONLY);
    fileOutput = open("output-part3", O_WRONLY | O_TRUNC | O_CREAT, 0666);

    if (fileOutput == -1 || fileInput == -1) {
        perror("[ERROR] Failed to open the output file");
    }

    //Initi the values from agrs
    offsetBit = pagesize;
    createPageTable(pages);
    createPhysicalSpace(frames);

    int error = 0;
    while (read(fileInput, &virtualAddress, sizeof(unsigned long)) == sizeof(unsigned long)) {
//        printf("Virtual Address is 0x%lx\n", virtualAddress);
        offset = virtualAddress & (pow(2, offset) -1); //
//        printf("offset: %lx\n", offset);

        virtualAddress = virtualAddress >> offsetBit;
        error = convertPageToFrame(virtualAddress, &frame);

        if (error == -1) {
            fprintf(stderr, "[ERROR] in converting page to frame\n");
            exit(2);
        }

        physicalAddress = frame << offsetBit; // Bitwise left shift to get the physical base address
        physicalAddress = physicalAddress + offset;

        write(fileOutput, &physicalAddress, sizeof(unsigned long));
    }

    printf("# of page faults: %d\n", getPageFaults());

    freePhysical();
    cleanUpVirtual();

    return 0;
}