PROCS = 4

BINDIR = bin
CFLAGS = -Wall -W -pedantic -std=c99 -Wno-unused-parameter
LIBS = -lm
MPICC = mpicc
RUN = mpirun
RUN_OPTS = -np $(PROCS)

gen_test_data: gen_test_data.c
	$(CC) $(CFLAGS) -o $(BINDIR)/gen_test_data $^ $(LIBS)

mpi_convex_hull: mpi_convex_hull.c mpi_convex_hull.h
	$(MPICC) $(CFLAGS) -o $(BINDIR)/mpi_convex_hull $^ $(LIBS)

all: mpi_convex_hull gen_test_data

clean:
	rm -f *.o
	rm -f bin/*

run:
	$(RUN) $(RUN_OPTS) $(BINDIR)/mpi_convex_hull
