MPICC = mpicc
CFLAGS = -std=gnu99 -Wall -O3 -fopenmp
PROG = getcpu_mpi_omp

$(PROG): $(PROG).c
	$(MPICC) $(CFLAGS) $< -o $@
