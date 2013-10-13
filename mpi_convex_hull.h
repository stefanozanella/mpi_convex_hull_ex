#include <stdio.h>
#include <mpi.h>

/*
 * Wraps MPI initialization/finalization code, so that independent apps don't
 * need to take care about that boilerplate.
 */
int exec_mpi_app(int argc, char* argv[]);

/*
 * MPI Convex Hull
 */
int mpi_convex_hull(int argc, char* argv[]);