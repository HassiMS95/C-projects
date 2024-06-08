#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// static page table with the following fnum numbers
unsigned int PT[32] = {2, 4, 1, 7, 3, 5, 6, 0};
unsigned int p = 5, f = 3, d = 7;
unsigned long LA, PA;
unsigned int pnum, fnum, dnum; /* offset */

int main(int argc, char *argv[]) {

	// Checks the number of parameters being used
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <infile> <outfile>\n", argv[0]);
		return 1;
	}

	// Opens the input file in binary mode
	FILE *infile = fopen(argv[1], "rb+");
	if (infile == NULL) {
		fprintf(stderr, "Failed to open input file.\n");
		return 1;
	}

	// Opens the output file in binary mode
	FILE *outfile = fopen(argv[2], "wb+");
	if (outfile == NULL) {
		fprintf(stderr, "Failed to open output file.\n");
		fclose(infile);
		return 1;
	}

	// Reads each logical address into an unsigned long variable
	while(fread(&LA, sizeof(unsigned long), 1, infile) == 1) {

		dnum = LA & 0x7F;

		// Get the page number from the logical address
		pnum = (LA >> d);

		// Maps a page number from the page table to the frame number
		fnum = PT[pnum];

		// Happens when a page fault occurs
		if(fnum == -1) {
			printf("Page fault: invalid page number.\n");
			fclose(infile);
			fclose(outfile);
			return 1;
		}

		// Computes the physical address of a variable
		PA = (fnum << d) + dnum;

		// Writes the physical address to the output file
		fwrite(&PA, sizeof(unsigned long), 1, outfile);
	}

	// Closes both input and output files
	fclose(infile);
	fclose(outfile);

	return 0;
}
