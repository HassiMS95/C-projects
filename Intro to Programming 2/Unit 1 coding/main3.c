#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size, i;
    double sum = 0;
    float avg;
    int * myData;

    scanf("%d", &size);

    myData = (int*) calloc(size, sizeof(int));

    for (i = 0; i < size; ++i) {
        myData[i] = i;
        sum = sum + myData[i];
    }

    for (i = 0; i < size; ++i) {
        printf("%d ", myData[i]);
    }

    avg = (double) sum/size;
    printf("\naverage: %0.2f", avg);
    free(myData);

    return 0;
}