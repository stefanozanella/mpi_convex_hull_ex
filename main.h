#include <stdio.h>
#include <mpi.h>

/*
 * Wraps MPI initialization/finalization code, so that independent apps don't
 * need to take care about that boilerplate.
 */
int exec_mpi_app(int (*app)(int, char**), int argc, char* argv[]);

/*
 * Applications
 */

// Simple multi-process hello world
int hello_world(int argc, char* argv[]);

// Simple one-way msg exchange between 2 procs
int ping(int argc, char* argv[]);
void ping_sender(int rank);
void ping_receiver(int rank);
