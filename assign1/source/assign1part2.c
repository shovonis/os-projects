#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include "phypages.h"
#include "pagetable.h"

int main(int argc, char *argv[]) {

    //Given Page Table information//
    unsigned long offsetBit = 7;
    unsigned long virtualAddress;
    int fileInput;
    int fileOutput;
//    int pageTable[32] = {2, 4, 1, 7, 3, 5, 6};

    unsigned long offset;
    unsigned long frame;
    unsigned long physicalAddress;

    //Check input params
    if (argc != 2) {
        fprintf(stderr, "Invalid Params or file name %s \n", argv[0]);
        exit(1);
    }

    //Try to open the output file
    fileInput = open(argv[1], O_RDONLY);
    fileOutput = open("output-part2", O_WRONLY | O_TRUNC | O_CREAT, 0666);

    if (fileOutput == -1 || fileInput == -1) {
        perror("[ERROR] Failed to open the output file");
    }

    createPageTable(32);
    createPhysicalSpace(8);

    int error = 0;
    while (read(fileInput, &virtualAddress, sizeof(unsigned long)) == sizeof(unsigned long)) {
//        printf("Virtual Address is 0x%lx\n", virtualAddress);
        offset = virtualAddress & 127; // total size of the virtual page is 128 byte
//        printf("offset: %lx\n", offset);

        virtualAddress = virtualAddress >> offsetBit;
        error = convertPageToFrame(virtualAddress, &frame);

        if (error == -1) {
            fprintf(stderr, "[ERROR] on converting page to frame\n");
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