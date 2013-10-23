#include "point_cloud_geom.h"

ulong parse_long(char *str) {
  char *end;
  ulong ret = strtoul(str, &end, 10);

  if (strlen(end) > 0) {
    printf("Error: size must be an integer, but %s was provided.\n", str);
    exit(1);
  }

  return ret;
}

point_cloud_t init_point_cloud(ulong size) {
  point_cloud_t ret;
  ret.pc = (point_t*) malloc(size * sizeof(point_t));
  ret.size = size;

  return ret;
}

int point_compare(const void *p_ptr1, const void *p_ptr2) {
  point_t p1 = *((point_t*)p_ptr1);
  point_t p2 = *((point_t*)p_ptr2);

  coord_t ret = p1.x - p2.x;
  if (ret == 0l) { ret = p1.y - p2.y; };

  return ret;
}

