ss: part1 part2 part3

part1: assign1part1.c
	gcc -o assign1part1 -Wall assign1part1.c
	./assign1part1 part1sequence
	md5sum output-part1

part2: assign1part2.c pagetable.c phypages.c
	gcc -o assign1part2 -Wall assign1part2.c phypages.c pagetable.c
	./assign1part2 part2sequence
	md5sum output-part2

part3: assign1part3.c pagetable.c phypages.c
	gcc -o assign1part3 -Wall assign1part3.c phypages.c pagetable.c -lm
	./assign1part3 128 4096 1024 part2sequence
	md5sum output-part3

clean:
	rm -fr *.o

