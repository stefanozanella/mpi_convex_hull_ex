#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>

typedef struct point {
  float x;
  float y;
} point_t; // A point of our system

typedef float coord_t;  // A point's coordinate

typedef unsigned long ulong_t;

void print_usage(char* prog_name) {
  printf("Usage: %s <size>\n", prog_name);
  printf("Parameters:\n");
  printf("  size: number of test points to generate\n");
}

void init_cloud_generation() {
  srand(time(NULL));
}

coord_t rand_coord(float limit) {
  ulong_t safe_limit = limit == 0 ? 1l : limit;

  return ((coord_t) rand() / (coord_t) RAND_MAX - 0.5) * safe_limit;
}

point_t random_point(float limit) {
  return (point_t) { rand_coord(limit), rand_coord(limit) };
}

ulong_t parse_long(char *str) {
  char *end;
  ulong_t ret = strtoul(str, &end, 10);

  if (strlen(end) > 0) {
    printf("Error: size must be an integer, but %s was provided.\n", str);
    exit(1);
  }

  return ret;
}

double now()
{
  struct timeval t;
  struct timezone tzp;
  gettimeofday(&t, &tzp);

  return t.tv_sec + t.tv_usec*1e-6;
}

point_t* init_point_cloud(ulong_t size) {
  return (point_t*) malloc(size * sizeof(point_t));
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
void init_round_limits(float *output, ulong_t rounds) {
  for (ulong_t k = 0; k < rounds; k++) {
    output[k] = 1.0 - log((1.0 + k) / rounds);
  }
}

void generate_point_cloud(ulong_t size, point_t* output) {
  ulong_t rounds = size / 1e2;
  float *round_limits = (float*) malloc(rounds * sizeof(float));
  init_round_limits(round_limits, rounds);

  ulong_t round_size = size / rounds;

  for (ulong_t k = 0; k < size; k++) {
    output[k] = random_point(round_limits[k/round_size]);
  }
}

int epsilon_equal(coord_t c1, coord_t c2) {
  return fabs((c1 - c2) / c2) <= 0.0001;
}

int point_compare(const void *p_ptr1, const void *p_ptr2) {
  point_t p1 = *((point_t*)p_ptr1);
  point_t p2 = *((point_t*)p_ptr2);

  coord_t ret = p1.x - p2.x;
  if (epsilon_equal(ret, 0.0)) { ret = p1.y - p2.y; };

  if (epsilon_equal(ret, 0.0)) {
    ret = 0;
  }
  else {
    ret = (0.0 < ret) - (ret < 0.0);
  }

  return ret;
}

void store_point_cloud(point_t* pc, int pc_size, FILE* out) {
  for (int k = 0; k < pc_size; k++) {
    fprintf(out, "%.9f\t%.9f\n", pc[k].x, pc[k].y);
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage(argv[0]);
    exit(1);
  }

  ulong_t point_cloud_size = parse_long(argv[1]);

  char out_filename[255];
  sprintf(out_filename, "data/cloud_%lu.dat", point_cloud_size);

  printf("Generating a cloud with %lu points\n", point_cloud_size);

  double start_time = now();
  init_cloud_generation();
  point_t* point_cloud = init_point_cloud(point_cloud_size);
  generate_point_cloud(point_cloud_size, point_cloud);
  double end_time = now();

  printf("Generated %lu points in %.6fs.\n", point_cloud_size, end_time - start_time);

  printf("Calculating the convex hull...\n");
  start_time = now();
  qsort(point_cloud, point_cloud_size, sizeof(point_t), &point_compare);
  end_time = now();
  printf("Found the convex hull in %.6fs.\n", end_time - start_time);

  printf("Storing points into %s...", out_filename);
  FILE *out_fp;
  if ((out_fp = fopen(out_filename, "w")) == NULL) {
    printf("\nError: cannot open file %s. Aborting.\n", out_filename);
    exit(1);
  }

  store_point_cloud(point_cloud, point_cloud_size, out_fp);

  printf("done.\n");
  fclose(out_fp);
}
