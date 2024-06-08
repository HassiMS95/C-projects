#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Student_s {
	int id;
    char name[10];
} Student;

void sortStudents(Student students[], int size);
void print(Student students[], int size);
Student searchStudent(Student students[], int size, int studentID);