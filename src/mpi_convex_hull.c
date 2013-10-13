#include "mpi_convex_hull.h"

int main(int argc, char* argv[]) {
  return exec_mpi_app(argc, argv);
}

int exec_mpi_app(int argc, char* argv[]) {
  int retval;

  MPI_Init(&argc, &argv);
  retval = mpi_convex_hull(argc, argv);
  MPI_Finalize();

  return retval;
}

/*
 * MPI Convex Hull
 */
int mpi_convex_hull(int argc, char* argv[]) {
  int rank, size;
  int retval = 0;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  switch (rank) {
    case 0:
      retval = ch_master(argc, argv);
      break;
    default:
      break;
  }

  return retval;
}

/*
 * The master process, which is in charge to also act as a coordinator for the
 * whole CPU set.
 */
int ch_master(int argc, char* argv[]) {
  if (argc < 2) {
    print_usage(argv[0]);
    return 1;
  }

  char *point_cloud_file = argv[1];
  FILE *point_cloud_fp;
  if ((point_cloud_fp = fopen(point_cloud_file, "r")) == NULL) {
    printf("\nError: cannot open file %s. Aborting.\n", point_cloud_file);
    return 1;
  }

  return 0;
}

/*
 * Help screen.
 */
void print_usage(char* prog_name) {
  printf("Usage: %s <input_file>\n", prog_name);
  printf("Parameters:\n");
  printf("  input_file: path of the file containing point cloud data\n");
}
