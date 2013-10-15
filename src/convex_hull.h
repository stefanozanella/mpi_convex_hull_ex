#ifndef CH_H
#define CH_H

#include "point_cloud_geom.h"

void convex_hull_monotone_chain(point_t* cloud, int cloud_size, point_t* out_hull, ulong* out_size);
coord_t turn_direction(point_t p1, point_t p2, point_t p3);

#endif
