#include <stdio.h>
#include <stdlib.h>
#include "route-records.h"

RouteRecord* createRecords (FILE* fileIn) {
// Creates the records of the flights
	int records = 0;
	int i = 0;
	int j = 0;

	char buffer[500];

	fgets(buffer, 500, fileIn);
	while(fgets(buffer, 500, fileIn) != NULL) {
		records++;
	}

	RouteRecord* newRecord = (RouteRecord*)malloc(records*sizeof(RouteRecord));

	for (i = 0, i < records; i++) {
		for (j = 0; j < 6; j++) {
			newRecord[i].passengerCounts[j] = 0;
		}
	}

	rewind(fileIn);
	return newRecord;
}

int fillRecords (RouteRecord* r, FILE* fileIn) {
/*
format the csv records using 
fgets and sscanf to enter into array (newRecord)

parse out each line in file using fgets and sscanf
*/
	int month;
    char type[20];
    char buffer[500];
    char origin[4];
    char destination[4];
    char airline[3];
    int i = 1;
    int passengers = 0;
    int curIdx = 0;

    fgets(buffer, 500, fileIn);
    while(fgets(buffer, 500, fileIn) != NULL) {
        sscanf(buffer, "%d,%[^,],%[^,],%[^,],%[^,],%d", &month, origin, destination, airline, type, &passengers);

        index = 0;
        index = findAirlineRoute(r, i, origin, destination, airline, index);

        if(index == -1) {
        	strcpy(r[curIdx].origin, origin);
            strcpy(r[curIdx].destination, destination);
            strcpy(r[curIdx].airline, airline);

            r[i].passengers[month-1] = passengers;
        }
        else{
           r[i].passengers[month - 1] = passengers; 
        }
        i++;
    }
    return i;      
}

int findAirlineRoute (RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx) {
// Recursive cases for finding airline routes
	if (curIdx >= length) {
		return -1;
	}
	else if ((strcmp(r[curIdx].origin, origin) == 0) && (strcmp(r[curIdx].destination, destination) == 0) && (strcmp(r[curIdx].airline, airline) == 0)) {
		return curIdx;
	}
	else {
		return findAirlineRoute(r, length + 1, origin, destination, airline, curIdx + 1);
	}
}

void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st) {
	// Searches through the records based on keys entered
	int found, total, avgPassengers, count, i, j, k = 0;
	int month[6];

	for (i = 0; i < length; i++){
		if (st == ORIGIN) {
			if (strcmp(r[i].origin, key1) == 0) {
				printf("%s (%s-%s)", r[i].airline, r[i].origin, r[i].destination);
				for (j = 0; j < 6; j++) {
					month[j] += r[i].passengerCounts[j];
					total += r[i].passengerCounts[j];
				}
				found++;
			}
		}
		else if (st == DESTINATION) {
			if (strcmp(r[i].destination, key1) == 0) {
				printf("%s (%s-%s)", r[i].airline, r[i].origin, r[i].destination);
				for (j = 0; j < 6; j++) {
					month[j] += r[i].passengerCounts[j];
					total += r[i].passengerCounts[j];
				}
				found++;
			}
		}
		else if (st == AIRLINE) {
			if (strcmp(r[i].airline, key1) == 0) {
				printf("%s (%s-%s)", r[i].airline, r[i].origin, r[i].destination);
				for (j = 0; j < 6; j++) {
					month[j] += r[i].passengerCounts[j];
					total += r[i].passengerCounts[j];
				}
				found++;
			}
		}
		else {
			if ((strcmp(r[i].origin, key1) == 0) && (strcmp(r[i].destination, key2) == 0)) {
				printf("%s (%s-%s)", r[i].airline, r[i].origin, r[i].destination);
				for (j = 0; j < 6; j++) {
					month[j] += r[i].passengerCounts[j];
					total += r[i].passengerCounts[j];
				}
				found++;
			}
		}
	}

	printf("\n%d matches were found.\n\n", found);
	printf("Statistics\nTotal Passengers: \t%d\n", total);

	avgPassengers = total / 6.0;

	for (k = 0; k < 6; k++) {
		printf("Total Passengers in Month %d: %d\n", k + 1, month[k]);
	}
	printf("\n\nAverage Passengers per Month: %.lf\n", avgPassengers);
}

void printMenu()
{
	printf("\n\n######### Airline Route Records Database MENU #########\n");
	printf("1. Search by Route\n");
	printf("2. Search by Origin Airport\n");
	printf("3. Search by Destination Airport\n");
	printf("4. Search by Airline\n");
	printf("5. Quit\n");
	printf("Enter your selection: ");
}