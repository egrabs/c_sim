CC=gcc
CFLAGS=-I.
DEPS = arrayutils.h cell.h vectorutils.h
OBJ = cell.o vectorutils.o arrayutils.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sim_engine: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
