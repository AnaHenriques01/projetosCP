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

    // Get the total number of processes running
    int num_processes;
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    int iteration = 1;
    int K = atoi(argv[2]), num_threads = atoi(argv[3]);
    float sum[K * 2];
    int num_elems[K];
    float centroids[K * 2];
    int converged = 0;

    int points_chunks = N / num_processes;
    float *scattered_points = (float *)malloc(points_chunks * 3 * sizeof(float));

    omp_set_num_threads(num_threads);

    init(K, sum, num_elems, centroids);

    // The root process sends chunks of the array points to different processes
    MPI_Scatter(points, points_chunks * 3, MPI_FLOAT, scattered_points, points_chunks * 3, MPI_FLOAT, 0, MPI_COMM_WORLD);

    addToClosestCluster(0, K, num_elems, centroids, sum, scattered_points, rank, points_chunks);
    while (!converged && iteration <= MAX_ITERATIONS)
    {
        int allEquals = addToClosestCluster(iteration, K, num_elems, centroids, sum, scattered_points, rank, points_chunks);
        if (allEquals == N)
            converged = 1;
        else
            iteration++;
    }
    free(scattered_points);

    // Only process with rank 0 can print the output
    if (rank == 0)
    {
        printf("N = %d, K = %d\n", N, K);
        for (int i = 0; i + 1 < K * 2; i += 2)
        {
            printf("Center: (%.3f, %.3f) : Size: %d\n", centroids[i], centroids[i + 1], num_elems[i / 2]);
        }
        printf("Iterations: %d\n", iteration - 1);
    }
    // Finzalize MPI
    MPI_Finalize();

    return 0;
}
