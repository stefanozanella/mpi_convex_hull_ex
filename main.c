#include "main.h"

int main(int argc, char* argv[]) {
  return exec_mpi_app(hello_world, argc, argv);
}

int exec_mpi_app(int (*app)(int, char**), int argc, char* argv[]) {
  int retval;

  MPI_Init(&argc, &argv);
  retval = (*app)(argc, argv);
  MPI_Finalize();

  return retval;
}

int hello_world(int argc, char* argv[]) {
  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  printf("Hello world from process %d / %d\n", rank, size);

  return 0;
}
