#include "point_cloud_io.h"

void store_point_cloud(point_t* pc, int pc_size, FILE* out) {
  fprintf(out, PC_SIZE_FMT, pc_size);
  for (int k = 0; k < pc_size; k++) {
    fprintf(out, PC_POINT_FMT, pc[k].x, pc[k].y);
  }
}

