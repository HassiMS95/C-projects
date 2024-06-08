#include "point.h"

void midpoint(struct Point p1,struct Point p2,struct Point *temp)
{
    temp->x=(p1.x+p2.x)/2;
    temp->y=(p1.y+p2.y)/2;
    temp->z=(p1.z+p2.z)/2;
}

void distance(struct Point p1,struct Point p2,double *d)
{
    
    *d=sqrt(pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2) + pow((p1.z-p2.z),2));
}