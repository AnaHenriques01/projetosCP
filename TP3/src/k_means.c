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

    int iteration = 1, notOver = 1;
    int K = atoi(argv[2]), num_threads = atoi(argv[3]);
    float sum[K * 2];
    int num_elems[K];
    float centroids[K * 2];
    float old_centroids[K * 2];

    omp_set_num_threads(num_threads);

    init(K, sum, num_elems, centroids);
    addToClosestCluster(0, K, num_elems, centroids, old_centroids, sum);

    while (iteration <= 20)
    {
        int allEquals = 0;
        printf("new iteration %d\n\n", iteration);
        memcpy(old_centroids, centroids, sizeof(float) * K * 2);
        addToClosestCluster(iteration, K, num_elems, centroids, old_centroids, sum);
        if (rank == 0)
        {
            for (int j = 0; j + 1 < K * 2; j += 2)
            {
                printf("old_centroids %d: (%f,%f)\n", j / 2, old_centroids[j], old_centroids[j + 1]);
                printf("centroids %d: (%f,%f)\n", j / 2, centroids[j], centroids[j + 1]);
                printf("\n");
                float ah = 0.467867 - 0.482817;
                printf("ah: %d\n", ah);
                float dif1 = centroids[j] - old_centroids[j];
                printf("dif1: %d\n", dif1);
                float dif2 = centroids[j + 1] - old_centroids[j + 1];
                printf("dif2: %d\n", dif2);
                if (dif1 < 0)
                {
                    dif1 = (centroids[j] - old_centroids[j]) * (-1);
                    printf("dif1: %d\n", dif1);
                }
                if (dif2 < 0)
                {
                    dif2 = (centroids[j + 1] - old_centroids[j + 1]) * (-1);
                    printf("dif2: %d\n", dif2);
                }
                if (dif1 == 0.000 && dif2 == 0.000)
                {
                    allEquals++;
                    printf("so far: %d\n", allEquals);
                }
            }
        }
        printf("allEquals %d\n\n", allEquals);
        if (allEquals == K)
            notOver = 0;
        iteration++;
    }

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
