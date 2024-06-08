#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int valid;
	int frame;
} PTE;

PTE PT[32];
unsigned long LA, PA;
unsigned int p = 5, f = 3, d = 7; // offset
unsigned int pnum, fnum, dnum;

int pageFaults = 0;
int CLK = 0;
int freeframes[8] = {0, 1, 1, 1, 1, 1, 1, 1};
int LRUcount[8] = {0};
int revmap[8] = {-1};

// Finds an empty frame in the page table
int findEmptyFrame() {
	for (int i = 0; i < 8; i++) {
		// if the free frame is found
		if (freeframes[i] == 1) {
			freeframes[i] = 0;
			return 1;
		}
	}
	// if no free frame is found
	return -1;
}

// Selects the victim frame for replacement using LRU
int selectVictimLRU() {
	int minCount = LRUcount[0];
	int victim = 0;
	for (int i = 0; i < 8; i++) { // find the least recently used frame
		if (LRUcount[i] < minCount) {
			minCount = LRUcount[i];
			victim = i;
		}
	}
	freeframes[victim] = 1; // Victim frame is free
	return victim; // Returns the index of the victim frame
}

int main(int argc, char *argv[]) {
	
	// Checks the number of parameters being used
	if (argc != 3) {
		printf("Usage: part2 <infile> <outfile>\n");
		return 1;
	}

	// Opens the input file in binary mode
	FILE *infile = fopen(argv[1], "rb+");
	if (infile == NULL) {
		printf("Error: Failed to open input file.\n");
		return 1;
	}

	// Opens the output file in binary mode
	FILE *outfile = fopen(argv[2], "wb+");
	if (outfile == NULL) {
		printf("Error: Failed to open output file.\n");
		fclose(infile);
		return 1;
	}

	// Reads each line in the input file until EOF
	while(fread(&LA, sizeof(unsigned long), 1, infile) == 1) {
		// increment the clock counter
		CLK++;
		pnum = LA >> d;
		dnum = LA & 0x07F;

		// Calculates and write the physical address if page is in the page table
		if (PT[pnum].valid == 1) {
			fnum = PT[pnum].frame;
			PA = (fnum << d) + dnum;
			fwrite(&PA, sizeof(unsigned long), 1, outfile);
			LRUcount[fnum] = CLK;
		}
		else { // if page is not in the page table
			// First finds the empty frame
			int x = findEmptyFrame();
			// if the empty frame exists
			if (x >= 0) {
				PT[pnum].frame = x;
				PT[pnum].valid = 1;
				fnum = PT[pnum].frame;
				PA = (fnum << d) + dnum;
				fwrite(&PA, sizeof(unsigned long), 1, outfile);
				revmap[x] = pnum;
				LRUcount[fnum] = CLK;
			}
			// if there is not an empty frame
			else { 
				int y = selectVictimLRU();
				PT[revmap[y]].valid = 0;
				PT[pnum].frame = y;
				PT[pnum].valid = 1;
				fnum = PT[pnum].frame;
				PA = (fnum << d) + dnum;
				fwrite(&PA, sizeof(unsigned long), 1, outfile);
				LRUcount[fnum] = CLK;
				revmap[fnum] = pnum;
				// Increment the number of page faults
				pageFaults++;
			}
		}
	}

	// Prints the total number of page faults found
	printf("Part 2 page faults: %d\n", pageFaults);

	return 0;
}