#include "student.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERROR NO ARGS\n");
        return 0;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");

    if (!file) {
        printf("ERROR FILE NOT OPEN\n");
        return 0;
    }

    int size = 0;
    char line[20];
    while (!feof(file)) {
        fscanf(file," %s", line);
        size++;
    }

    Student *students = malloc(sizeof(Student)*size);
    fseek(file, 0, SEEK_SET);
    int i=0;

    while (!feof(file)) {
        fscanf(file," %s", line);
        char *token = strtok(line, ",");
        students[i].id = atoi(token);
        token = strtok(NULL, "\n");
        strcpy(students[i].name, token);
        i++;
    }

    fclose(file);
    print(students, size);
    sortStudents(students, size);
    print(students, size);
    int studentID;
    scanf("%d", &studentID);
    Student searchedStudent = searchStudent(students, size, studentID);
    printf("(%d,%s)\n", searchedStudent.id, searchedStudent.name);

    return 0;

}