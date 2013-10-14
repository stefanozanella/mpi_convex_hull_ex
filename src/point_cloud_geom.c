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

point_t* init_point_cloud(ulong size) {
  return (point_t*) malloc(size * sizeof(point_t));
}
