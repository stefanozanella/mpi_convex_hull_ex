#include "convex_hull.h"

void convex_hull_monotone_chain(point_t* cloud, int cloud_size, point_t* out_hull, ulong* out_size) {
  point_t* hull = out_hull;
  int j = 0;

  for (int k = 0; k < cloud_size; k++) {
    while (j >= 2 && turn_direction(hull[j-2], hull[j-1], cloud[k]) <= 0) --j;
    hull[j++] = cloud[k];
  }

  for (int k = cloud_size-2, t = j+1; k >= 0; --k) {
    while (j >= t && turn_direction(hull[j-2], hull[j-1], cloud[k]) <= 0) --j;
    hull[j++] = cloud[k];
  }

  out_hull = hull;
  *out_size = j;
}

coord_t turn_direction(point_t p1, point_t p2, point_t p3) {
  return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

