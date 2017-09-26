//
// Created by rifatul islam on 9/25/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    //Given Page Table information//
    unsigned long offsetBit = 7;
    unsigned long virtualAddress;
    int fileInput;
    int fileOutput;
    int pageTable[32] = {2, 4, 1, 7, 3, 5, 6};

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
    fileOutput = open("output-part1", O_WRONLY | O_TRUNC | O_CREAT, 0666);

    if (fileOutput == -1 || fileInput == -1) {
        perror("Failed to open the output file");
    }

    while (read(fileInput, &virtualAddress, sizeof(unsigned long)) == sizeof(unsigned long)) {
        printf("Virtual Address is 0x%lx\n", virtualAddress);
        offset = virtualAddress & 127; // total size of the virtual page is 128 byte
        printf("offset: %lx\n", offset);

        unsigned long pageTableIndex = virtualAddress >> offsetBit; //Bitwise right shift to get the page index
        frame = pageTable[pageTableIndex];

        physicalAddress = frame << offsetBit; // Bitwise left shift to get the physical base address
        physicalAddress = physicalAddress + offset;

        printf("Frame is: %ld and Virtual index is: %ld, Physical Address: 0x%lX\n", frame, pageTableIndex,
               physicalAddress);

        write(fileOutput, &physicalAddress, sizeof(unsigned long));
    }

    return 0;
}