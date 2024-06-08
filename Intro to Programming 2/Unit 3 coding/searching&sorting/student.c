#include "student.h"

void sortStudents(Student students[], int size) {
    for (int i=0; i<size-1; i++) {
        for (int j=0; j<size-i-1; j++) {
            if (students[j].id > students[j+1].id) {
                Student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }
}

void print(Student students[], int size) {
    for (int i=0; i<size; i++) {
        printf("(%d,%s) -> ", students[i].id, students[i].name);
    }
    printf("\n");
}


Student searchStudent(Student students[], int size, int studentID) {
    for (int i=0; i<size; i++) {
        if (students[i].id == studentID) {
            return students[i];
        }
    }
    
    return students[0];
}