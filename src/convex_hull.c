#include "convex_hull.h"

point_cloud_t convex_hull_monotone_chain(point_cloud_t cloud, point_cloud_t hull) {
  int j = 0;

  for (int k = 0; k < cloud.size; k++) {
    while (j >= 2 && turn_direction(hull.pc[j-2], hull.pc[j-1], cloud.pc[k]) <= 0) --j;
    hull.pc[j++] = cloud.pc[k];
  }

  for (int k = cloud.size-2, t = j+1; k >= 0; --k) {
    while (j >= t && turn_direction(hull.pc[j-2], hull.pc[j-1], cloud.pc[k]) <= 0) --j;
    hull.pc[j++] = cloud.pc[k];
  }

  hull.size = j;
  return hull;
}

coord_t turn_direction(point_t p1, point_t p2, point_t p3) {
  return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

