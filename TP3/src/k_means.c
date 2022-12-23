#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <mpi.h>

#include "../include/utils.h"

#define MAX_ITERATIONS 20

int main(int argc, char *argv[])
{
    // Init MPI
    MPI_Init(&argc, &argv);

    // Get the rank of the current process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int iteration = 1;
    int K = atoi(argv[2]), num_threads = atoi(argv[3]);
    float sum[K * 2];
    int num_elems[K];
    float centroids[K * 2];

    omp_set_num_threads(num_threads);

    init(K, sum, num_elems, centroids);
    addToClosestCluster(0, K, num_elems, centroids, sum);

    while (iteration <= MAX_ITERATIONS)
    {
        addToClosestCluster(iteration, K, num_elems, centroids, sum);
        iteration++;
    }

    // Only process with rank 0 can print the output
    if (rank == 0)
    {
        printf("N = %d, K = %d\n", N, K);
        printf("Center: (%.3f, %.3f) : Size: %d\n", centroids[0], centroids[1], num_elems[0]);
        printf("Center: (%.3f, %.3f) : Size: %d\n", centroids[2], centroids[3], num_elems[1]);
        printf("Center: (%.3f, %.3f) : Size: %d\n", centroids[4], centroids[5], num_elems[2]);
        printf("Center: (%.3f, %.3f) : Size: %d\n", centroids[6], centroids[7], num_elems[3]);
        printf("Iterations: %d\n", iteration - 1);
    }

    // Finzalize MPI
    MPI_Finalize();

    return 0;
}
