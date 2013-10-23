#ifndef CH_H
#define CH_H

#include "point_cloud_geom.h"

point_cloud_t convex_hull_monotone_chain(point_cloud_t pc);
coord_t turn_direction(point_t p1, point_t p2, point_t p3);

#endif
