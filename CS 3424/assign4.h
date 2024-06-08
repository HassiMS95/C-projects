#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char course_Name [80];
    char course_Sched [4];
    unsigned course_Hours ;
    unsigned course_Size ;
    unsigned padding ;
} COURSE;