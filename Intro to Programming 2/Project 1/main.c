#include <stdio.h>
#include <time.h>
#include "dicegame.h"

int main(int argc, char* argv[])
{
	srand(time(NULL));

	int p1 = 0;
	int p2 = 0;

	int numRounds, currentPlayer, dice, points, i;

	// Ask the user for the number of rounds to run the game
	printf("Enter the number of rounds: ");
	scanf("%d". &numRounds);

	// Starting the game
	printPlayerPoints(p1, p2);
	
	// Main for-loop for each round played until all rounds are complete
	for (i = 1; i <= numRounds; ++i) {
		
		ROUNDTYPE type = getRoundType();
		dice = getRandomNumber(1,6);
		points = getRoundPoints(roundtype);
		currentPlayer = getRandomNumber(1,2);
		
		printf("Round %d\n", i);
		printf("--------\n");
		printf("Player\t: %d\n", currentPlayer);
	    
	    // Prints info for each round played
		printRoundInfo(type, dice, points);
		
		// Player 2 wins if the dice is even, otherwise loses points if dice is odd
		if (currentPlayer == 2) {
			if (dice % 2 == 0) {
				p2 += points;
			}
			else {
				p2 -= points;
				// Player 1 becomes the current player when Player 2 loses.
				currentPlayer = 1;
			}
		}
		// Player 1 wins if the dice is odd, otherwise loses points if dice is odd
		else {
			if (dice % 2 == 1) {
				p1 += points;
			}
			else {
				p1 -= points;
				// Playar 2 becomes the current player when Player 1 loses
				currentPlayer = 2;
			}
		}

		// Keeps track of the points each playar has
		// and who is currently winning so far.
		printPlayerPoints(p1, p2);
	}
	printf("\nGAME OVER!!\n");
	
	// Decides who won the game completely
	if(p1 > p2) {
		printf("P1 Won\n");
	}
	else {
		printf("P2 Won\n");	
	}
	
	return 0;
}