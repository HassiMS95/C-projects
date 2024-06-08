#ifndef LINKEDLIST
#define LINKEDLIST

typedef struct LLNode {
	int id;
	char name[10];
	double gpa;
	struct LLNode* next;
} LLNode;

LLNode* createNode(int id, char name[], double gpa);
LLNode* insertNode(LLNode* head, LLNode* nd);
double averageGPA(LLNode* head);
void printLL(LLNode* head);
LLNode* destroyLL(LLNode* head);

#endif