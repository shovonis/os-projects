ss: part1 part2 part3

part1: assign1part1.c
	gcc -o assign1part1 -Wall assign1part1.c

part2: assign1part2.c pagetable.c phypages.c
	gcc -o assign1part2 -Wall assign1part2.c phypages.c pagetable.c
part3: assign1part3.c pagetable.c phypages.c
	gcc -o assign1part3 -Wall assign1part3.c phypages.c pagetable.c -lm


#run1:    	
#         ./assign3part1 part1testsequence

#run2: 
#	./assign3part2 part1testsequence

#run3: 
#	./assign3part2 part2sequence

clean: 
	*.o

