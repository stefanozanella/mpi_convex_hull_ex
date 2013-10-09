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

void generate_point_cloud(ulong_t size, point_t* output) {
  #define STEP_NO 10

  /* This LUT is used to give the final cloud a more randomic, less squared
   * shape.
   */
  const float round_limits[STEP_NO] = {
    1.0,
    2.0,
    3.0,
    3.3,
    4.2,
    4.6,
    4.7,
    4.8,
    4.9,
    5.0 };
  ulong_t step_size = size / STEP_NO;

  for (ulong_t k = 0; k < size; k++) {
    output[k] = random_point(round_limits[k/step_size]);
  }
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
