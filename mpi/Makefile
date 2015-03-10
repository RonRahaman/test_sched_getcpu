MPICC = mpicc
CFLAGS = -std=gnu99 -Wall -O3
PROG = getcpu_mpi

$(PROG): $(PROG).c
	$(MPICC) $(CFLAGS) $< -o $@
