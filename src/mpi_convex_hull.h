#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#include "point_cloud_io.h"

/*
 * Represents a point in MPI communications
 */
MPI_Datatype mpi_point_t;

/*
 * Wraps MPI initialization/finalization code, so that independent apps don't
 * need to take care about that boilerplate.
 */
int exec_mpi_app(int argc, char* argv[]);

/*
 * Initialize MPI utilities like custom data types
 */
void mpi_initialize_runtime();
void mpi_init_point_type();

/*
 * MPI Convex Hull
 */
int mpi_convex_hull(int argc, char* argv[]);
int ch_master(int argc, char* argv[]);
int ch_slave(int argc, char* argv[], int rank);
void bcast_point_cloud_size(int* size);
void chan_step_1(point_t* pc, int pc_size);
void print_usage(char *app_name);
