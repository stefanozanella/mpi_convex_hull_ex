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

/*
 * Hello world
 */
int hello_world(int argc, char* argv[]) {
  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  printf("Hello world from process %d / %d\n", rank, size);

  return 0;
}

/*
 * Ping
 */
int ping(int argc, char* argv[]) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  switch (rank) {
  case 0:
    ping_sender(rank);
    break;

  case 1:
    ping_receiver(rank);
    break;
  }

  printf("#%d is exiting\n", rank);
  return 0;
}

void ping_sender(int rank) {
  int buf = 123456;
  MPI_Send(&buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  printf("#%d has sent %d to %d\n", rank, buf, 1);
}

void ping_receiver(int rank) {
  MPI_Status status;
  int buf;
  MPI_Recv(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
  printf("#%d has received %d from %d\n", rank, buf, 0);
}
