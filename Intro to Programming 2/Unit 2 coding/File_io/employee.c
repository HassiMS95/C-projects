#include "employee.h"
#include <stdio.h>
#include <stdlib.h>

Employee* readData(char *filename, int *size) {
	FILE *f;
	f = fopen(filename, "r");
	if(f == NULL) {
		printf("Error: File not exist!\n");
		exit(1);
	}

	int n = 0;
	char buffer[80];
	while(fgets(buffer, 80, f)!=NULL) {
		n++;
	}

	Employee *emp = (Employee*)malloc(n*sizeof(Employee));
	rewind(f);

	for(int i=0; i<n; i++) {
		fscanf(f, "%s%d%lf", emp[i].name, &emp[i].id, &emp[i].salary);
	}
	*size = n;
	fclose(f);
	return emp;
}

Employee getBestEmployee(Employee *emp, int size) {
	int k = 0;
	for(int i=1; i<size; i++) {
		if(emp[i].salary>emp[k].salary) {
			k = i;
		}
	}

	return emp[k];
}

void writeData(char *filename, Employee emp) {
	FILE *f;
	f = fopen(filename, "w");
	fprintf(f, "%s %d %d", emp.name, emp.id, (int)emp.salary);
	fclose(f);
}