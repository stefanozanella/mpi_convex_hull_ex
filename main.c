#include "main.h"

int main(int argc, char* argv[]) {
  return exec_mpi_app(ping, argc, argv);
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

int ping(int argc, char* argv[]) {
  int buf, rank;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    buf = 123456;
    MPI_Send(&buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    printf("#%d has sent %d to %d\n", rank, buf, 1);
  }
  else if (rank == 1) {
    MPI_Status status;
    MPI_Recv(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    printf("#%d has received %d from %d\n", rank, buf, 0);
  }

  printf("#%d is exiting\n", rank);
  return 0;
}
