#include "point_cloud_io.h"

void store_point_cloud(point_cloud_t pc, FILE* out) {
  fprintf(out, PC_SIZE_FMT, pc.size);
  for (int k = 0; k < pc.size; k++) {
    fprintf(out, PC_POINT_FMT, pc.pc[k].x, pc.pc[k].y);
  }
}

point_cloud_t load_point_cloud(int pc_size, FILE* in) {
  point_cloud_t pc = init_point_cloud(pc_size);
  for (int k = 0; k < pc_size; k++) {
    point_t pt;
    fscanf(in, PC_POINT_FMT, &pt.x, &pt.y);
    pc.pc[k] = pt;
  }

  return pc;
}
