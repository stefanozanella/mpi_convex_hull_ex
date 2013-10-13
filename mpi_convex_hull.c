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

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  printf("Hello world from process %d / %d\n", rank, size);

  return 0;
}
