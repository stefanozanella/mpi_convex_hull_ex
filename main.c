#include "main.h"

int main(int argc, char* argv[]) {
  int retval;

  MPI_Init(&argc, &argv);
  retval = exec_parallel();
  MPI_Finalize();

  return retval;
}

int exec_parallel() {
  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  printf("Hello world from process %d / %d\n", rank, size);

  return 0;
}
