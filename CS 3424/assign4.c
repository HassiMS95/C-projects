#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assign4.h"

void printMenu() {
    printf("Enter one of the following actions or press CTRL-D to exit.\n");
    printf("C - create a new course record\n");
    printf("U - update an existing course record\n");
    printf("R - read an existing course record\n");
    printf("D - delete an existing course record\n");
    printf("F - Find/search and compare course records\n");
}

int main() {
    FILE *fp, *ft;
    char option;
    COURSE c;
    int courseNum, cn;
    char courseName[40];
    long int recSize;

    fp = fopen("courses.dat", "r+");
    if (fp == NULL) {
       fp = fopen("courses.dat", "w+");
       if (fp == NULL) {
            printf("Cannot open file.");
            exit(1);
       }
    }

    recSize = sizeof(c);

    while(1) {
        printMenu();
        printf("Choose your option: ");
        scanf("\n%c", &option);
        switch(option) {
        // creates a course record
            case 'C':
            case 'c':
                printf("Enter course number: ");
                scanf(" %d", &courseNum);
                printf("Enter course name: ");
                scanf(" %s", c.course_Name);
                printf("Enter course schedule: ");
                scanf(" %s", c.course_Sched);
                printf("Enter course credit hours: ");
                scanf(" %d", &c.course_Hours);
                printf("Enter course enrollment: ");
                scanf(" %d", &c.course_Size);

                break;
        // updates a course record
            case 'U':
            case 'u':
                break;
        // reads the course records
            case 'R':
            case 'r':
                break;
        // deletes a course record
            case 'D':
            case 'd':
                printf("Enter a course number: ");
                scanf(" %d", &courseNum);
                int found = 0;
                if (){
                    print("course number was successfully deleted.")
                }
                else if () {
                    print("ERROR: course not found");
                }
                else {
                    printf("ERROR: invalid option");
                }
                fclose(fp);
                break;
        // finds a course records
            case 'F':
            case 'f':
                printf("Enter a search phrase:\t");
                break;
        }
    }

    return 0;
}