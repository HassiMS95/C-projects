#include "point.h"

int main()
{
    struct Point p1,p2,temp;
    scanf("%lf",&p1.x);
    scanf("%lf",&p1.y);
    scanf("%lf",&p1.z);
    
    scanf("%lf",&p2.x);
    scanf("%lf",&p2.y);
    scanf("%lf",&p2.z);
    
    midpoint(p1,p2,&temp);
    printf("midpoint : %.2lf, %.2lf, %.2lf",temp.x,temp.y,temp.z);
    
    double dist;
    distance(p1,p2,&dist);
    printf("\ndistance : %.2lf",dist);
    
    return 0;   
}