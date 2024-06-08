#define CHAMPION

typedef enum ChampionRole { MAGE, FIGHTER, SUPPORT, TANK} ChampionRole;

typedef struct Champion
{
	ChampionRole role;
	int level;
	struct Champion* next;
} Champion;

Champion* createChampion();
Champion* addChampion(Champion *head, Champion *c);
Champion* buildChampionList(int n);
void printChampionList(Champion *head);
Champion* removeChampion(Champion *head);
Champion* destroyChampion(Champion *head); 