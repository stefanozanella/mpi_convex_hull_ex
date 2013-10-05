BIN = bin/hello
PROCS = 4

CFLAGS = -Wall -W -pedantic
MPICC = mpicc
RUN = mpirun
RUN_OPTS = -np $(PROCS)

all: *.c
	$(MPICC) $(CFLAGS) -o $(BIN) $^

clean:
	rm -f *.o
	rm -f bin/*

run: all
	$(RUN) $(RUN_OPTS) $(BIN)

.PHONY: all clean run
