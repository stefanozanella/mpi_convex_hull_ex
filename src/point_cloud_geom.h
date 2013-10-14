#ifndef PC_GEOM_H
#define PC_GEOM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned long ulong;
typedef signed long coord_t;  // A point's coordinate

typedef struct point {
  coord_t x;
  coord_t y;
} point_t; // A point on our system

ulong parse_long(char *str);
point_t* init_point_cloud(ulong size);

#endif
