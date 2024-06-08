#include <stdio.h>
#include <stdlib.h>
#include "employee.h"

int main() {
	int size;
	Employee* emps = readData("a6-input.txt", &size);
	Employee bestEmp = getBestEmployee(emps, size);
	writeData("a6-output.txt", bestEmp);
	
	return 0;
}