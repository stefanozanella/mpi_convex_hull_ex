PROCS = 4

BINDIR = bin
CFLAGS = -Wall -W -pedantic -std=c99 -Wno-unused-parameter
LIBS = -lm
MPICC = mpicc
RUN = mpirun
RUN_OPTS = -np $(PROCS)

GEN_TEST_DATA_BIN = $(BINDIR)/gen_test_data
MPI_CONVEX_HULL_BIN = $(BINDIR)/mpi_convex_hull

GEN_TEST_DATA_SOURCE = src/gen_test_data.c
MPI_CONVEX_HULL_SOURCE = src/mpi_convex_hull.c src/mpi_convex_hull.h

gen_test_data: $(GEN_TEST_DATA_SOURCE)
	$(CC) $(CFLAGS) -o $(GEN_TEST_DATA_BIN) $^ $(LIBS)

mpi_convex_hull: $(MPI_CONVEX_HULL_SOURCE)
	$(MPICC) $(CFLAGS) -o $(MPI_CONVEX_HULL_BIN) $^ $(LIBS)

all: mpi_convex_hull gen_test_data

clean:
	rm -f *.o
	rm -f bin/*

run:
	$(RUN) $(RUN_OPTS) $(MPI_CONVEX_HULL_BIN) $(in)
