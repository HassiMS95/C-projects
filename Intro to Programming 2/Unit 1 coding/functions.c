#include <stdio.h>
#include <math.h>
#include "functions.h"

double average(int a[])
{
    int sum=0;
    for(int i = 0; i < LENGTH; i++)
    {
        sum = sum + a[i];
    }
    return (double) sum/LENGTH;
}

void quadraticFormula(double a,double b,double c,double *x1,double *x2) {
   double squareRt = sqrt(pow(b,2) - 4*a*c);
   *x1 = (-b + squareRt) /(2*a);
   *x2 = (-b - squareRt) /(2*a);  
}