#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "champion.h"

void endGame(Champion* p1, Champion* p2) {
	printf("============ GAME OVER  =============\n\n");
	printf("Player 1 ending champion list: ");
	printChampionList(p1);
	printf("\n");
	printf("Player 2 ending champion list: ");
	printChampionList(p2);
	printf("\n");

	if (p1 < p2) {
		printf("Player 1 ran out of champions. Player 2 wins.");
	}
	else if (p1 > p2) {
		printf("Player 2 ran out of champions. Player 1 wins.");
	}
	else {
		print("TIE -- both players ran out of champions.");
	}
}

int main(int argc, char *argv[]) {
	srand(time(NULL));

	if(argc != 2) {
		printf("ERROR: Invalid number of command line arguments\n");
		exit();
	}

	int numChamps = atoi(argv[1]);

	printf("============= PLAYER 1 V PLAYER 2 SHOWDOWN ============\n\n");
	Champion* p1 = buildChampionList(n);
	Champion* p2 = buildChampionList(n);

	Champion* p1current;
	Champion* p2current;
	
	printf("Player 1: ");
	printChampionList(p1);
	printf("\n");
	printf("Player 2: ");
	printChampionList(p2);
	printf("\n");

	int round = 0;
	for(round = 1; round < numChamps + 1; round++) {
		printf("----- ROUND %d -----\n", round);
		printf("Player 1: ");
		printChampionList(p1);
		printf("Player 2: ");
		printChampionList(p2);
		if(p1->role == p2->role){
			if(p1->role == MAGE && p1->level > p2->level){
				printf("Player 1 is a MAGE and Player 2 is a MAGE\n");
				printf("Player 1 (MAGE) wins and gains one new champion.\n");
				printf("Player 2 (MAGE) loses one champion.\n\n");
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p2 = removeChampion(p2);
				p1current = createChampion();
				p1 = addChampion(p1,p1current);
				
			}
			if(p1->role == MAGE && p1->level < p2->level){
				printf("Player 1 is a MAGE and Player 2 is a MAGE\n");
				printf("Player 1 (MAGE) loses one champion.\n");
				printf("Player 2 (MAGE) wins and gains one new champion.\n\n");
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p2current = createChampion();
				p2 = addChampion(p2,p2current);
			}
			if(p1->role == FIGHTER){
				printf("Player 1 is a FIGHTER and Player 2 is a FIGHTER\n");
				printf("Player 1 (FIGHTER) gains one champion.\n");
				printf("Player 2 (FIGHTER) gains one new champion.\n\n");
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p1current = createChampion();
				p1 = addChampion(p1,p1current);
				p2current = createChampion();
				p2 = addChampion(p2,p2current);
			}
			if(p1->role == SUPPORT){
				printf("Player 1 is a SUPPORT and Player 2 is a SUPPORT\n");
				printf("Both players lose one champion");
				p1 = removeChampion(p1);
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p2 = removeChampion(p2);
				p2current = createChampion();
				p2 = addChampion(p2,p2current);
			}
			if(p1->role == TANK){
				printf("Player 1 is a TANK and Player 2 is a TANK\n");
				printf("Nothing happens - no penalty or reward.\n\n");
			}
		}
			if(p1->level > p2->level){
				if(p1->role == MAGE){
					if(p2->role == FIGHTER){
				printf("Player 1 is a MAGE and Player 2 is a FIGHTER\n");
				printf("Player 1 (MAGE) wins and gains one champion.\n");
				printf("Player 2 (FIGHTER) loses.\n\n");
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p1current = createChampion();
				p1 = addChampion(p1,p1current);
			}
					if(p2->role == SUPPORT){
				printf("Player 1 is a MAGE and Player 2 is a SUPPORT\n");
				printf("Player 1 (MAGE) wins and gains one champion.\n");
				printf("Player 2 (SUPPORT) loses two champions.\n\n");
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p2 = removeChampion(p2);
				p2 = removeChampion(p2);
				p1current = createChampion();
				p1 = addChampion(p1,p1current);
			}
		}
			if(p1->role == FIGHTER){
				if(p2->role == MAGE){
				printf("Player 1 is a FIGHTER and Player 2 is a MAGE\n");
				printf("Player 1 (FIGHTER) wins.\n");
				printf("Player 2 (MAGE) loses one champion.\n\n");
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p2 = removeChampion(p2);
			}
				if(p2->role == SUPPORT){
				printf("Player 1 is a FIGHTER and Player 2 is a SUPPORT\n");
				printf("Player 1 (FIGHTER) wins.\n");
				printf("Player 2 (SUPPORT) loses one champion.\n\n");
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p2 = removeChampion(p2);
			}
		}
			if(p1->role == SUPPORT){
				if(p2->role == MAGE){
				printf("Player 1 is a SUPPORT and Player 2 is a MAGE\n");
				printf("Player 1 (SUPPORT) wins and gains two champion.\n");
				printf("Player 2 (MAGE) loses one champions.\n\n");
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p2 = removeChampion(p2);
				p1current = createChampion();
				p1 = addChampion(p1,p1current);
				p1current = createChampion();
				p1 = addChampion(p1,p1current);				
			}
				if(p2->role == FIGHTER){
				printf("Player 1 is a SUPPORT and Player 2 is a FIGHTER\n");
				printf("Player 1 (SUPPORT) wins and gains one champion.\n");
				printf("Player 2 (FIGHTER) loses.\n\n");
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p1current = createChampion();
				p1 = addChampion(p1,p1current);			
			}
		}
		}
		if(p1->role == TANK){
			if(p2->role == MAGE){
				printf("Player 1 is a TANK and Player 2 is a MAGE\n");
				printf("Player 1 (TANK) loses one champion.\n");
				printf("Player 2 (MAGE) wins and gains a new champion.\n\n");
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p1 = removeChampion(p1);
				p2current = createChampion();
				p2 = addChampion(p2,p2current);
			}		
			if(p2->role == SUPPORT){
				printf("Player 1 is a TANK and Player 2 is a SUPPORT\n");
				printf("Player 1 (TANK) wins and gains one champion.\n");	
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p1current = createChampion();
				p1 = addChampion(p2,p2current);				
			}
			if(p2->role == FIGHTER){
				printf("Player 1 is a TANK and Player 2 is a MAGE\n");
				printf("Player 1 (TANK) loses.\n");
				printf("Player 2 (FIGHTER) wins and gains a new champion.\n\n");
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p2current = createChampion();
				p2 = addChampion(p2,p2current);	
			}
		}
		if(p2->role == TANK){
			if(p1->role == MAGE){
				printf("Player 1 is a MAGE and Player 2 is a TANK\n");
				printf("Player 1 (MAGE) wins and gains one champion.\n");	
				printf("Player 2 (TANK) loses one champion.\n");
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p2 = removeChampion(p2);
			}		
			if(p1->role == SUPPORT){
				printf("Player 1 is a SUPPORT and Player 2 is a TANK\n");
				printf("Player 1 (SUPPORT) loses.\n");
				printf("Player 2 (TANK) wins and gains a new champion.\n\n");
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p2current = createChampion();
				p2 = addChampion(p2,p2current);				
			}
			if(p1->role == FIGHTER){
				printf("Player 1 is a FIGHTER and Player 2 is a TANK\n");
				printf("Player 1 (FIGHTER) wins and gains a new champion.\n\n");
				printf("Player 2 (TANK) loses.\n");
				p1 = removeChampion(p1);
				p2 = removeChampion(p2);
				p1current = createChampion();
				p1 = addChampion(p1,p1current);	
			}		
		}
		if(p1->level == p2->level && (p1->role!=TANK && p2->role!=TANK)&&(p1->role!=p2->role)) {
			printf("Player 1 and Player 2 are tied.\nNothing happens - no penalty or reward.\n\n");
		}
	}

	endGame(p1, p2);
	destroyChampionList(p1);
	destroyChampionList(p2);

	return 0;
}