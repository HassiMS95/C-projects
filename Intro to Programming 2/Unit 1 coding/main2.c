#include <stdio.h>
#include <math.h>

int main()
{
    int i;
    const int LENGTH = 10;
    float avg, xi, sd, sum = 0;

    float arr[LENGTH];

    for (i = 0; i < LENGTH; ++i) {
        scanf("%f", &arr[i]);
    }

    for (i = 0; i < LENGTH; ++i) {
        sum = sum + arr[i];
    }

    avg = sum/LENGTH;
    printf("average: %0.2f\n", avg);

    for (i = 0; i < 10; ++i) {
        xi = xi + pow((arr[i]-avg), 2);
    }

    sd = sqrt(xi/LENGTH);
    printf("standard deviation: %0.2f\n", sd);

    return 0;
}