#define _GNU_SOURCE
#include <sched.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc,  char **argv) {
  int stat, n_procs, my_rank, my_cpu, name_len;
  char *name;

  MPI_Init(&argc, &argv);

  stat = MPI_Comm_size(MPI_COMM_WORLD, &n_procs);
  assert(stat == MPI_SUCCESS);

  stat = MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  assert(stat == MPI_SUCCESS);

  name = (char *) malloc(MPI_MAX_PROCESSOR_NAME * sizeof(char));
  stat = MPI_Get_processor_name(name, &name_len);
  assert(stat == MPI_SUCCESS);

  my_cpu = sched_getcpu();

  for (int i=0; i<n_procs; i++) {
    if (my_rank == i) {
      printf("rank %2d,  node '%s',  cpu %2d\n", my_rank, name, my_cpu);
      fflush(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }
  
  MPI_Finalize();
}
