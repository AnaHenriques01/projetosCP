#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "../include/utils.h"

#define MAX_ITERATIONS 20

int main(int argc, char *argv[])
{

    // int notOver = 1;
    int allEquals = 0, count = 1;
    int K = atoi(argv[2]), num_threads = atoi(argv[3]);
    float sum[K * 2];
    int num_elems[K];
    float centroids[K * 2];

    printf("N = %d, K = %d\n", N, K);

    omp_set_num_threads(num_threads);

    init(K, sum, num_elems, centroids);
    addToClosestCluster(0, K, num_elems, centroids, sum);

    // if(N <= K) notOver = 0;   // BEST CASE
    /* do{
         allEquals = addToClosestCluster(count, K, threads, num_elems, centroids, sum);
         //if(allEquals == N) notOver = 0;
         //else count++;
         count++;
     } while (count < 20);*/

    while (count <= MAX_ITERATIONS)
    {
        allEquals = addToClosestCluster(count, K, num_elems, centroids, sum);
        count++;
    }

    // ----------------------------------------- OUTPUT DO PROGRAMA:
    int i, i2 = 0;
    for (i = 0; i + 1 < K * 2; i += 2)
    {
        printf("Center: (%.3f, %.3f) : Size: %d\n", centroids[i], centroids[i + 1], num_elems[i2]);
        i2++;
    }
    printf("Interations: %d\n", count - 1);
    // ------------------------------------------------------------

    return 0;
}