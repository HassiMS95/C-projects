#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

LLNode* createNode(int id, char name[], double gpa) {
    LLNode *n = (LLNode*)malloc(sizeof(LLNode));
    n->id = id;
    n->gpa = gpa;
    strcpy(n->name, name);
    n->next = NULL;

    return n;
}

LLNode* insertNode(LLNode* head, LLNode* nd) {
    LLNode* n = nd;
    LLNode* cur = head;
    LLNode* prev = NULL;

    while ((cur != NULL) && (strcmp(cur->name, nd->name) <= 0)) {
        prev = cur;
        cur = cur->next;
    }

    if (prev == NULL) {
        n->next = cur;
        return n;
    }

    prev->next = n;
    n->next = cur;
    return head;
}

double averageGPA(LLNode* head) {
    double avg;
    double total = 0;
    int i = 0;
    LLNode* t = head;

    while (t != NULL) {
        total += t->gpa;
        i++;
        t = t->next;
    }

    avg = total / i;
    printf("Average = %.2lf\n", avg);
    return avg;
}

void printLL(LLNode* head) {
    LLNode* t = head;
    while (t != NULL) {
        printf("(%d,%s,%.2lf) -> ", t->id, t->name, t->gpa);
        t = t->next;
   }
}

LLNode* destroyLL(LLNode* head) {
    while (head != NULL) {
        LLNode* t = head;
        head = head->next;
        free(t);
   }
   return head;
}