PROCS = 4
BINDIR = bin

MPICC = $(@which mpcc 2>&1 > /dev/null)
CFLAGS = -std=c99
ifeq ($(shell which mpcc 2> /dev/null),)
	MPICC = mpicc
	CFLAGS += -Wall -W -pedantic -Wno-unused-parameter
else
	MPICC = mpcc
endif
RUN = mpirun

LIBS = -lm
RUN_OPTS = -np $(PROCS)

GEN_TEST_DATA_BIN = $(BINDIR)/gen_test_data
MPI_CONVEX_HULL_BIN = $(BINDIR)/mpi_convex_hull

COMMON_SOURCE = src/point_cloud_io.c src/point_cloud_geom.c src/convex_hull.c
GEN_TEST_DATA_SOURCE = src/gen_test_data.c $(COMMON_SOURCE)
MPI_CONVEX_HULL_SOURCE = src/mpi_convex_hull.c $(COMMON_SOURCE)

prep:
	mkdir -p $(BINDIR)

gen_test_data: $(GEN_TEST_DATA_SOURCE)
	$(CC) $(CFLAGS) -o $(GEN_TEST_DATA_BIN) $^ $(LIBS)

mpi_convex_hull: $(MPI_CONVEX_HULL_SOURCE)
	$(MPICC) $(CFLAGS) -o $(MPI_CONVEX_HULL_BIN) $^ $(LIBS)

all: prep mpi_convex_hull gen_test_data

clean:
	rm -f *.o
	rm -f bin/*

run:
	$(RUN) $(RUN_OPTS) $(MPI_CONVEX_HULL_BIN) $(in)

.PHONY : prep clean
