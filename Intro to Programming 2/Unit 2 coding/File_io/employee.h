#ifndef Employee_h
#define Employee_h

typedef struct Employee
{
	char name[10];
	int id;
	double salary;
} Employee;

Employee* readData(char* filename, int* size);
Employee getBestEmployee(Employee* emps, int size);
void writeData(char* filename, Employee emp);

#endif