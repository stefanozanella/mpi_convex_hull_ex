#ifndef PC_GEOM_H
#define PC_GEOM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned long ulong;
typedef signed long coord_t;

typedef struct point {
  coord_t x;
  coord_t y;
} point_t;

ulong parse_long(char *str);
point_t* init_point_cloud(ulong size);
int point_compare(const void *p_ptr1, const void *p_ptr2);

#endif
