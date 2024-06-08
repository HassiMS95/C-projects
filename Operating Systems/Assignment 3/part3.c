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
int findEmptyFrame(int* freeframes) {
	for (int i = 0; i < 8; i++) {
		// if the free frame is found
		if (freeframes[i] == 1) {
			freeframes[i] = 0;
			return i;
		}
	}
	// if no free frame is found
	return -1;
}

// Selects the victim frame for replacement using LRU
int selectVictimLRU(int* LRUcount) {
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

	for (int i = 0; i < 32; i++) {
		PT[i].valid = 0;
	}

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
			int x = findEmptyFrame(freeframes);
			// if the empty frame exists
			if ((PT[pnum].frame = x) != -1) {
				// Increment the number of page faults
				pageFaults++;
				PT[pnum].valid = 1;
				fnum = PT[pnum].frame;
				PA = (fnum << d) + dnum;
				revmap[x] = pnum;
				fwrite(&PA, sizeof(unsigned long), 1, outfile);
				LRUcount[fnum] = CLK;
			}
			// if there is not an empty frame
			else {
				// Increment the number of page faults
				pageFaults++;
				int y = selectVictimLRU(LRUcount);
				PT[revmap[y]].valid = 0;
				PT[pnum].frame = y;
				PT[pnum].valid = 1;
				fnum = PT[pnum].frame;
				PA = (fnum << d) + dnum;
				fwrite(&PA, sizeof(unsigned long), 1, outfile);
				LRUcount[fnum] = CLK;
				revmap[fnum] = pnum;
			}
		}
	}

	// Prints the total number of page faults found
	printf("Part 2 page faults: %d\n", pageFaults);
	fclose(infile);
	fclose(outfile);

	return 0;
}