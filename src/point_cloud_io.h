#ifndef PC_IO
#define PC_IO

#include <stdlib.h>
#include <stdio.h>

#include "point_cloud_geom.h"

#define PC_SIZE_FMT "# size=%d\n"
#define PC_POINT_FMT "%ld\t%ld\n"

void store_point_cloud(point_t* pc, int pc_size, FILE* out);

#endif
