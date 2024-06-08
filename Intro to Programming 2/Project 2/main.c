#include <stdio.h>
#include <stdlib.h>
#include "route-records.h"

int main( int argc, char *argv[] ) {
    int choice = 0;

    if(argc != 2) {
        printf("ERROR: Missing file name and end the program");
        return -1;
    }
  
    printf("Opening <%s>", argv[0]);
    FILE* fileIn = NULL;
    fileIn = fopen(argv[1], "r");

    if(fileIn == NULL) {
        printf("ERROR: Could not open file");
        return -1;
    }           
    
    RouteRecord *myFlight = createRecords(fileIn);
    int length = fillRecords(myFlight, fileIn); 

    printf("Unique route created by airline: %d\n",length);
    fclose(fileIn);
    
    char buffer[20];
    char key1[30];
    char key2[30];

    SearchType st;

    printMenu();		
    
    // Switch/case statement to handle all menu options
	switch(choice) {
    	case 1:
            st = ROUTE;
            printf("\nEnter origin: ");
            scanf("%s", key1);
            printf("\nEnter destination: ");
            scanf("%s", key2);
            printf("\n\nSearching by route...\n");
            searchRecords(myFlight, length, key1, key2, st);
            break;
        case 2:
            st = ORIGIN;
            printf("\nEnter origin: ");
            scanf("%s", key1);
            printf("Search by origin...\n");
            searchRecords(myFlight, length, key1, key2, st);
            break;
        case 3:
            st = DESTINATION;
            printf("\nEnter destination: ");
            scanf("%s", key1);
            printf("\nSearching by destination...\n");
            searchRecords(myFlight, length, key1, key2, st);
            break;
        case 4:
            st = AIRLINE;
            printf("\nEnter airline: ");
            scanf("%s", key1);
            printf("Search by airline...\n");
            searchRecords(myFlight, length, key1, key2, st);
            break;
        case 5:
            printf("\nGood bye!\n");
            free(record);
            break;
        default:
            // When a non-integer value is entered
            printf("\nInvalid choice.");
            break;
    } while (choice != 5);

    return 0;        
}