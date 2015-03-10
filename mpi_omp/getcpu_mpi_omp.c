#define _GNU_SOURCE
#include <sched.h>
#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc,  char **argv) {
  int stat, n_procs, my_rank, name_len;
  char *name;

  MPI_Init(&argc, &argv);

  stat = MPI_Comm_size(MPI_COMM_WORLD, &n_procs);
  assert(stat == MPI_SUCCESS);

  stat = MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  assert(stat == MPI_SUCCESS);

  name = (char *) malloc(MPI_MAX_PROCESSOR_NAME * sizeof(char));
  stat = MPI_Get_processor_name(name, &name_len);
  assert(stat == MPI_SUCCESS);


  for (int i=0; i<n_procs; i++) {
    if (my_rank == i) {
#pragma omp parallel default(none) shared(name, my_rank, stdout)
      {
        int my_thread = omp_get_thread_num();
        int n_threads = omp_get_num_threads();
        int my_cpu = sched_getcpu();
        for (int j=0; j<n_threads; j++) {
          if (my_thread == j) {
            printf("node '%s', rank %2d, thread %2d, cpu %2d\n", name, my_rank, my_thread, my_cpu);
            fflush(stdout);
          }
#pragma omp barrier
        }
      }
      fflush(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }

  MPI_Finalize();
}
