#define DICEGAME_H

typedef enum ROUNDTYPE{BONUS, DOUBLE, REGULAR} ROUNDTYPE;

int getRandomNumber(int min, int max);
ROUNDTYPE getRoundType();
int getRoundPoints (ROUNDTYPE roundType);
void printPlayerPoints (int p1, int p2);
void printRoundInfo (ROUNDTYPE t, int dice, int points);