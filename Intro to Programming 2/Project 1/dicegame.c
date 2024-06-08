#include "dicegame.h"
#include <stdio.h>

int getRandomNumber(int min, int max) {
	return rand()%(max - min + 1) + min;
}

ROUNDTYPE getRoundType() {

	int n = getRandomNumber(0,9);

	if (n <= 1) {
		return BONUS;
	}
	else if (n <= 3) {
		return DOUBLE;
	}
	else {
		return REGULAR;
	}
}

int getRoundPoints (ROUNDTYPE roundType) {
	points = getRandomNumber(1,10) * 10;

	switch(roundType) {
	case REGULAR:
		return points;
	case BONUS:
		return 200;		
	case DOUBLE:
		return 2 * points;
	}
}	

void printPlayerPoints (int p1, int p2) {
	printf("P1: %d\n", p1);
	printf("P2: %d\n", p2);
}

void printRoundInfo (ROUNDTYPE t, int dice, int points) {
	printf("Type:\t");
	if (t == BONUS) {
		printf("BONUS\n");
	}
	else if (t == DOUBLE) {
		printf("DOUBLE\n");
	}
	else {
		printf("REGULAR\n");
	}
	printf("Dice:\t%d\n", dice);
	printf("Points:\t%d\n", points);
}