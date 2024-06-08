#include <stdio.h>

int main()
{
    int i;

    printf("Enter an integer: ");
    scanf("%d", &i);

    if ((i % 3 == 0) && (i % 5 == 0)) {
        printf("CS1714");
    }
    else if ((i % 3 == 0) && (i % 5 != 0)) {
        printf("CS");
    }
    else if ((i % 3 != 0) && (i % 5 == 0)) {
        printf("1714");
    }
    else {
        printf("ERROR");
    }

    return 0;
}