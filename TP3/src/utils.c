#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#include "../include/utils.h"

#include <mpi.h>

void init(int K, float sum[K * 2], int num_elems[K], float centroids[K * 2])
{
    int index = 0;
    srand(10);

    for (int p = 0; p + 2 < N * 3; p += 3)
    {
        points[p] = (float)rand() / RAND_MAX;
        points[p + 1] = (float)rand() / RAND_MAX;
        points[p + 2] = -1.0;
    }

    for (int i = 0; i + 1 < K * 2; i += 2)
    {
        centroids[i] = points[index];
        centroids[i + 1] = points[index + 1];
        num_elems[i / 2] = 1;
        points[index + 2] = (float)i / 2;
        sum[i] = points[index];
        sum[i + 1] = points[index + 1];
        index += 3;
    }
}

static inline float calculateDistance(float centroidX, float centroidY, float pointX, float pointY)
{
    return (centroidX - pointX) * (centroidX - pointX) + (centroidY - pointY) * (centroidY - pointY);
}

int addToClosestCluster(int iteration, int K, int num_elems[K], float centroids[K * 2], float sum[K * 2], int rank, int num_processes)
{
    int allEquals = 0;

    int points_chunks = N / num_processes;
    float *scattered_points = (float *)malloc(points_chunks * 3 * sizeof(float));

    if (iteration > 0)
    {
#pragma omp parallel for schedule(static)
        for (int j = 0; j < K * 2; j += 2)
        {
            num_elems[j / 2] = 0;
            sum[j] = 0.0;
            sum[j + 1] = 0.0;
        }
    }

    // Broadcast the centroids from the root process to every other process
    MPI_Bcast(centroids, K * 2, MPI_FLOAT, 0, MPI_COMM_WORLD);

    MPI_Scatter(points, points_chunks * 3, MPI_FLOAT, scattered_points, points_chunks * 3, MPI_FLOAT, 0, MPI_COMM_WORLD);

#pragma omp parallel for schedule(static) reduction(+                                                       \
                                                    : sum[:(K * 2)]) reduction(+                            \
                                                                               : num_elems[:K]) reduction(+ \
                                                                                                          : allEquals)
    for (int i = 0; i < points_chunks * 3; i = i + 3)
    {
        int previousCluster = scattered_points[i + 2];
        float minDistance = (centroids[0] - scattered_points[i]) * (centroids[0] - scattered_points[i]) + (centroids[1] - scattered_points[i + 1]) * (centroids[1] - scattered_points[i + 1]);
        int minCluster = 0;

        for (int j = 2; j < K * 2; j += 2)
        {
            float newDistance = (centroids[j] - scattered_points[i]) * (centroids[j] - scattered_points[i]) + (centroids[j + 1] - scattered_points[i + 1]) * (centroids[j + 1] - scattered_points[i + 1]);
            if (newDistance < minDistance)
            {
                minDistance = newDistance;
                minCluster = j / 2;
            }
        }

        scattered_points[i + 2] = minCluster;
        if (previousCluster == minCluster)
            allEquals++;
        sum[minCluster * 2] += scattered_points[i];
        sum[minCluster * 2 + 1] += scattered_points[i + 1];
        num_elems[minCluster]++;
    }

    float global_sum[K * 2];
    int global_num_elems[K];

    MPI_Gather(scattered_points, points_chunks * 3, MPI_FLOAT, points, points_chunks * 3, MPI_FLOAT, 0, MPI_COMM_WORLD);

    MPI_Reduce(sum, global_sum, K * 2, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(num_elems, global_num_elems, K, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (int j = 0; j + 1 < K * 2; j += 2)
        {
            int numElems = global_num_elems[j / 2];
            num_elems[j / 2] = global_num_elems[j / 2];
            centroids[j] = global_sum[j] / numElems;
            centroids[j + 1] = global_sum[j + 1] / numElems;
        }
    }
    free(scattered_points);
    return allEquals;
}