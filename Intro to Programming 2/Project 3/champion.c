#include <stdio.h>
#include <stdlib.h>
#include "champion.h"

Champion* createChampion() {
	Champion* newChamp = (Champion*)malloc(sizeof(Champion));
    *newChamp.level = (rand() % 4) + 1;
    switch(*newChamp.level) {
        case 1:
            newChamp->role = MAGE;
            newChamp->level = (rand()%(8 - 5 + 1))+ 5; 
        case 2:
            newChamp->role = FIGHTER;
            newChamp->level = (rand() % (4 - 1 + 1)) + 1;
        case 3:
            newChamp->role = SUPPORT;
            newChamp->level = (rand() % (6 - 3 + 1)) + 3;
        case 4:
            newChamp->role = TANK;
            newChamp->level = (rand() % (8 - 1 + 1)) + 1;
    }
    return newChamp;
}

Champion* addChampion(Champion *head, Champion *c) {
	if (head == NULL) {
		return c;
	}
	if (c == NULL) {
		return head;
	}
	if (c->level > head->level) {
		c->next = head;
	}
	return c;
}

Champion* buildChampionList(int n) {
	Champion* head = NULL;
	int i = 0;
	for (i = 0; i < n; ++i) {
		Champion* newChamp = createChampion();
		head = addChampion(head, newChamp);
	}
	return head;
}

void printChampionList(Champion *head) {
	char title = ' ';
	while (head != NULL) {
		if (head->role == MAGE) {
			title = 'M';
		}
		else if (head->role == FIGHTER) {
			title = 'F';
		}
		else if (head->role == SUPPORT) {
			title = 'S';
		}
		else {
			title = 'T';
		}
		printf("%c%d ", title, head->level);
		head = head->next;
	}
	printf("\n");
}

Champion* removeChampion(Champion *head) {
	if (*head == NULL) {
		return *head;
	}

	Champion* newHead = head->next;
	free(head);
	return newHead;
}

Champion* destroyChampionList(Champion *head){
	while (*head != NULL) {
		head = removeChampion(head);
	}
	return NULL;
}