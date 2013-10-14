#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <time.h>

#include "point_cloud_geom.h"
#include "point_cloud_io.h"

/*
 * Help screen.
 */
void print_usage(char* prog_name) {
  printf("Usage: %s <size>\n", prog_name);
  printf("Parameters:\n");
  printf("  size: number of test points to generate\n");
}

double now()
{
  struct timeval t;
  gettimeofday(&t, NULL);

  return t.tv_sec + t.tv_usec*1e-6;
}

void init_cloud_generation() {
  srand(time(NULL));
}

point_t* init_point_cloud(ulong size) {
  return (point_t*) malloc(size * sizeof(point_t));
}

coord_t rand_coord(coord_t limit) {
  coord_t safe_limit = limit == 0 ? 1l : limit;

  return ((float) rand() / (float) RAND_MAX - 0.5) * safe_limit * 1e2;
}

point_t random_point(coord_t limit) {
  return (point_t) { rand_coord(limit), rand_coord(limit) };
}

/*
 * If we allow each point to be picked in the same range, as the number of
 * points increase, the final shape will strongly resemble a square. Instead,
 * if we partition the number of points so that each subset of points is picked
 * from a range that is larger/smaller than the previous ones, we will obtain a
 * more randomic shape. In particular, we'll have less chances to have
 * collinear points on the convex hull, and its shape will be more fuzzy.
 * To improve the fuzziness around the edges, we'll use a logarithmic function;
 * the choice of the exact expression is rather customary and has been done on
 * an inspection basis (looking at the final picture of the point cloud).
 */
void init_round_limits(float *output, ulong rounds) {
  for (ulong k = 0; k < rounds; k++) {
    output[k] = 1.0 - log((1.0 + k) / rounds);
  }
}

void generate_point_cloud(ulong size, point_t* output) {
  ulong rounds = size / 1e2;
  float *round_limits = (float*) malloc(rounds * sizeof(float));
  init_round_limits(round_limits, rounds);

  ulong round_size = size / rounds;

  for (ulong k = 0; k < size; k++) {
    output[k] = random_point(round_limits[k/round_size]);
    //output[k] = random_point(size);
  }
}

int point_compare(const void *p_ptr1, const void *p_ptr2) {
  point_t p1 = *((point_t*)p_ptr1);
  point_t p2 = *((point_t*)p_ptr2);

  coord_t ret = p1.x - p2.x;
  if (ret == 0l) { ret = p1.y - p2.y; };

  return ret;
}

coord_t turn_direction(point_t p1, point_t p2, point_t p3) {
  return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

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

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage(argv[0]);
    exit(1);
  }

  ulong point_cloud_size = parse_long(argv[1]);

  char out_filename[255];
  sprintf(out_filename, "data/cloud_%lu.dat", point_cloud_size);

  printf("Generating a cloud with %lu points\n", point_cloud_size);

  double start_time = now();
  init_cloud_generation();
  point_t* point_cloud = init_point_cloud(point_cloud_size);
  generate_point_cloud(point_cloud_size, point_cloud);
  double end_time = now();

  printf("Generated %lu points in %.6fs.\n", point_cloud_size, end_time - start_time);

  printf("Storing points into %s...", out_filename);
  FILE *out_fp;
  if ((out_fp = fopen(out_filename, "w")) == NULL) {
    printf("\nError: cannot open file %s. Aborting.\n", out_filename);
    exit(1);
  }
  store_point_cloud(point_cloud, point_cloud_size, out_fp);

  printf("done.\n");
  fclose(out_fp);

  printf("Calculating the convex hull...\n");
  start_time = now();
  qsort(point_cloud, point_cloud_size, sizeof(point_t), &point_compare);
  point_t* hull = init_point_cloud(point_cloud_size);
  ulong hull_size = 0;
  convex_hull_monotone_chain(point_cloud, point_cloud_size, hull, &hull_size);
  end_time = now();
  printf("Found the convex hull in %.6fs.\n", end_time - start_time);

  char hull_filename[255];
  sprintf(hull_filename, "data/hull_%lu.dat", point_cloud_size);

  printf("Storing convex hull into %s...", hull_filename);
  FILE *hull_fp;
  if ((hull_fp = fopen(hull_filename, "w")) == NULL) {
    printf("\nError: cannot open file %s. Aborting.\n", hull_filename);
    exit(1);
  }
  qsort(hull, hull_size, sizeof(point_t), &point_compare);
  store_point_cloud(hull, hull_size, hull_fp);

  printf("done.\n");
  fclose(out_fp);
}
