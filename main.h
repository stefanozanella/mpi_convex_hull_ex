#include <stdio.h>
#include <mpi.h>

int exec_mpi_app(int (*app)(int, char**), int argc, char* argv[]);

int hello_world(int argc, char* argv[]);
