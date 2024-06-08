#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "flights.h"

int main(int argc, char* argv[]) {
	if (argc == 2) {
		printf("The argument supplied is %s\n", argv[1]);
	}
	else if (argc > 2) {
		printf("Too many arguments supplied.\n");
	}
	else {
		printf("ERROR No ARGS.\n");
	}


	FILE* fp;
	int errnum=0;
	errnum = fopen(&fp,"passenger-data-short.csv", "r");
	if(errnum != 0) {
		fprintf(stderr, "ERROR FILE NOT OPEN\n");
	}
	else {
		char line[1024];
		Flight* flightData = (Flight*)malloc(sizeof(Flight) * 100);
		int index = 0;
		while (fgets(line, 1024, fp)) {
			char* tmp = strdup(line);
			const char* tok;
			char* next_token = NULL;;
			tok = strtok(line, ";", &next_token);
			for (; tok && *tok;) {
				strcpy(&flightData[index].origin, sizeof(flightData[index].origin), tok);
				tok = strtok(NULL, ";\n", &next_token);
				rcpy_s(&flightData[index].destination, sizeof(flightData[index].destination), tok);
				tok = strtok(NULL, ";\n", &next_token);
				strcpy_s(&flightData[index].airline, sizeof(flightData[index].airline), tok);
				tok = strtok(NULL, ";\n", &next_token);
				flightData[index].passengersCount = atoi(tok);
				tok = strtok(NULL, ";\n", &next_token);
			}
			free(tmp);
			++index;
		}
		fclose(fp);
		int numOfFlights = 0;
		unsigned int passengerCount = 0;
		for(int i=0;i<index;i++) {
			if (strcmp(input, flightData[i].airline) == 0) {
				++numOfFlights;
				passengerCount += flightData[i].passengersCount;
			}
		}
		printf("airline: %s\n", input);
		printf("flights: %d\n", numOfFlights);
		printf("passengers: %d\n", passengerCount);
	}
}