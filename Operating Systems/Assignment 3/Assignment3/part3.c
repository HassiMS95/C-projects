#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int valid;
	int frame;
} PTE;

PTE PT[32];
unsigned long LA, PA;
unsigned int p, f, d; // offset
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
	if (argc != 6) {
		printf("Usage: part3 <bytesPerPage> <sizeOfVirtualMemory> <sizeOfPhysicalMemory> <infile> <outfile>\n");
		return 1;
	}

	int bytesPerPage = atoi(argv[1]);
	int sizeOfVirtualMemory = atoi(argv[2]);
	int sizeOfPhysicalMemory = atoi(argv[3]);

	// Calculates the offset sizes
	p = f = 0;
	while ((1 << p) * bytesPerPage < sizeOfVirtualMemory) {
		p++;
	}
	while ((1 << f) * bytesPerPage < sizeOfPhysicalMemory) {
		f++;
	}
	d = 22 - (p + f);

	// Opens the input file in binary mode
	FILE *infile = fopen(argv[4], "rb+");
	if (infile == NULL) {
		printf("Error: Failed to open input file.\n");
		return 1;
	}

	// Opens the output file in binary mode
	FILE *outfile = fopen(argv[5], "wb+");
	if (outfile == NULL) {
		printf("Error: Failed to open output file.\n");
		fclose(infile);
		return 1;
	}

	while(fread(&LA, sizeof(unsigned long), 1, infile) == 1) {
		CLK++;
		pnum = LA >> (d + f);
		dnum = LA & ((1 << (d + f)) - 1);

		if (PT[pnum].valid == 1) {
			fnum = PT[pnum].frame;
			PA = (fnum << (d + f)) + dnum;
			fwrite(&PA, sizeof(unsigned long), 1, outfile);
			LRUcount[fnum] = CLK;
		}
		else {
			int x = findEmptyFrame();
			if (x >= 0) {
				PT[pnum].frame = x;
				PT[pnum].valid = 1;
				fnum = PT[pnum].frame;
				PA = (fnum << (d + f)) + dnum;
				fwrite(&PA, sizeof(unsigned long), 1, outfile);
				revmap[x] = pnum;
				LRUcount[fnum] = CLK;
			}
			else {
				int y = selectVictimLRU();
				PT[revmap[y]].valid = 0;
				PT[pnum].frame = y;
				PT[pnum].valid = 1;
				fnum = PT[pnum].frame;
				PA = (fnum << (d + f)) + dnum;
				fwrite(&PA, sizeof(unsigned long), 1, outfile);
				LRUcount[fnum] = CLK;
				revmap[fnum] = pnum;
				pageFaults++;
			}
		}
	}

	printf("Part 3 page faults: %d\n", pageFaults);

	return 0;
}
