BIN = bin/hello
PROCS = 4

CFLAGS = -Wall -W -pedantic -std=c99 -Wno-unused-parameter
MPICC = mpicc
RUN = mpirun
RUN_OPTS = -np $(PROCS)

gen_test_data: gen_test_data.c
	$(CC) $(CFLAGS) -o bin/gen_test_data $^

all: *.c *.h
	$(MPICC) $(CFLAGS) -o $(BIN) $^

clean:
	rm -f *.o
	rm -f bin/*

run:
	$(RUN) $(RUN_OPTS) $(BIN)
