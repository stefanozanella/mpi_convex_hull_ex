PROCS = 4

BINDIR = bin
CFLAGS = -Wall -W -pedantic -std=c99 -Wno-unused-parameter
MPICC = mpicc
RUN = mpirun
RUN_OPTS = -np $(PROCS)

gen_test_data: gen_test_data.c
	$(CC) $(CFLAGS) -o $(BINDIR)/gen_test_data $^

mpi_convex_hull: main.c main.h
	$(MPICC) $(CFLAGS) -o $(BINDIR)/mpi_convex_hull $^

clean:
	rm -f *.o
	rm -f bin/*

run:
	$(RUN) $(RUN_OPTS) $(BINDIR)/mpi_convex_hull
