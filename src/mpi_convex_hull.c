#include "mpi_convex_hull.h"

int main(int argc, char* argv[]) {
  return exec_mpi_app(argc, argv);
}

int exec_mpi_app(int argc, char* argv[]) {
  int retval;

  MPI_Init(&argc, &argv);
  mpi_initialize_runtime();
  retval = mpi_convex_hull(argc, argv);
  MPI_Finalize();

  return retval;
}

void mpi_init_point_type() {
  MPI_Datatype mpi_point, types[1];
  int blockcounts[1];
  MPI_Aint offsets[1];

  blockcounts[0] = 2;
  offsets[0] = 0;
  types[0] = MPI_LONG;
  MPI_Type_struct(1, blockcounts, offsets, types, &mpi_point_t);
  MPI_Type_commit(&mpi_point_t);
}

void mpi_initialize_runtime() {
  mpi_init_point_type();
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
      retval = ch_slave(argc, argv, rank);
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

  int cloud_size = 0;
  if (fscanf(point_cloud_fp, PC_SIZE_FMT, &cloud_size) < 1) {
    printf("Cannot read point cloud size: please start the file with the following line:\n");
    printf("# size=<cloud size>\n");
  }

  printf("Reading point cloud of size %d.\n", cloud_size);
  point_t *point_cloud = init_point_cloud(cloud_size);
  load_point_cloud(point_cloud, cloud_size, point_cloud_fp);
  printf("[done]\n");

  bcast_point_cloud_size(&cloud_size);

  return 0;
}

int ch_slave(int argc, char *argv[], int rank) {
  int cloud_size;
  bcast_point_cloud_size(&cloud_size);
  printf("[%d] Advertised point cloud size: %d\n", rank, cloud_size);

  return 0;
}

void bcast_point_cloud_size(int *size) {
  MPI_Bcast(size, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

void chan_step_1(point_t* pc, int pc_size) {
}

/*
 * Help screen.
 */
void print_usage(char* prog_name) {
  printf("Usage: %s <input_file>\n", prog_name);
  printf("Parameters:\n");
  printf("  input_file: path of the file containing point cloud data\n");
}
