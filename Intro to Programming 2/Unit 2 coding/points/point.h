#include<stdio.h>
#include<math.h>

struct Point{
    double x;
    double y;
    double z;
};

void midpoint(struct Point p1,struct Point p2,struct Point *temp);
void distance(struct Point p1,struct Point p2,double *dist);