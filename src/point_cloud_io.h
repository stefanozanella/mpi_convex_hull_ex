#ifndef PC_IO
#define PC_IO

#include <stdlib.h>
#include <stdio.h>

#include "point_cloud_geom.h"

#define PC_SIZE_FMT "# size=%d\n"
#define PC_POINT_FMT "%ld\t%ld\n"

void store_point_cloud(point_cloud_t pc, FILE* out);
point_cloud_t load_point_cloud(int pc_size, FILE* in);

#endif
