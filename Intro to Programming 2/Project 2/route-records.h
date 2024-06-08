#define ROUTE_RECORDS

typedef struct RouteRecord
{
	char origin[4];
	char destination[4];
	char airline[3];
	int passengerCounts[6];
} RouteRecord;

RouteRecord* createRecords (FILE* fileIn);
int fillRecords (RouteRecord* r, FILE* fileIn);
int findAirlineRoute (RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx);
void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st);
void printMenu();

typedef enum SearchType { ROUTE, ORIGIN, DESTINATION, AIRLINE } SearchType;