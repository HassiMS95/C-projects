#include <stdio.h>
#include "functions.h"

int main()
{
    int arr[LENGTH];
    int a,b,c;
    double p,q;

    for(int i=0; i<LENGTH; i++)
    {
        scanf("%d",&arr[i]);
    }

    scanf("%d%d%d",&a,&b,&c);
    double avg = average(arr);
    printf("average: %.2lf\n",avg);
    
    quadraticFormula(a,b,c,&p,&q);
    printf("x1: %.2lf\n",p);
    printf("x2: %.2lf\n",q);

    return 0;
}