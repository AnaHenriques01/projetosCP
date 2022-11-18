#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "../include/utils.h"

#define MAX_ITERATIONS 20

int main(int argc, char *argv[])
{

    int iteration = 1;
    int K = atoi(argv[2]), num_threads = atoi(argv[3]);
    float sum[K * 2];
    int num_elems[K];
    float centroids[K * 2];

    printf("N = %d, K = %d\n", N, K);

    omp_set_num_threads(num_threads);

    init(K, sum, num_elems, centroids);
    addToClosestCluster(0, K, num_elems, centroids, sum);

    while (iteration <= MAX_ITERATIONS)
    {
        addToClosestCluster(iteration, K, num_elems, centroids, sum);
        iteration++;
    }

    // ----------------------------------------- OUTPUT DO PROGRAMA:
    int i, i2 = 0;
    for (i = 0; i + 1 < K * 2; i += 2)
    {
        printf("Center: (%.3f, %.3f) : Size: %d\n", centroids[i], centroids[i + 1], num_elems[i2]);
        i2++;
    }
    printf("Iterations: %d\n", iteration - 1);
    // ------------------------------------------------------------

    return 0;
}