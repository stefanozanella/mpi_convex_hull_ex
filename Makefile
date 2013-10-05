BIN = bin/hello
PROCS = 4

CFLAGS = -Wall -W -pedantic -std=c99
MPICC = mpicc
RUN = mpirun
RUN_OPTS = -np $(PROCS)

all: *.c *.h
	$(MPICC) $(CFLAGS) -o $(BIN) $^

clean:
	rm -f *.o
	rm -f bin/*

run:
	$(RUN) $(RUN_OPTS) $(BIN)

.PHONY: all clean run
