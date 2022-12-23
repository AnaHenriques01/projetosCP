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

void addToClosestCluster(int iteration, int K, int num_elems[K], float centroids[K * 2], float sum[K * 2])
{
    int startIndex, numElems, mpi_error;

    if (iteration > 0)
    {
#pragma omp parallel for schedule(static) private(numElems)
        for (int j = 0; j < K * 2; j += 2)
        {
            numElems = num_elems[j / 2];
            centroids[j] = sum[j] / numElems;
            centroids[j + 1] = sum[j + 1] / numElems;
            num_elems[j / 2] = 0;
            sum[j] = 0.0;
            sum[j + 1] = 0.0;
        }
    }

    if (iteration == 0)
        startIndex = K;
    else
        startIndex = 0;

#pragma omp parallel for schedule(static) reduction(+                          \
                                                    : sum[:K * 2]) reduction(+ \
                                                                             : num_elems[:K])
    for (int i = startIndex * 3; i + 2 < N * 3; i += 3)
    {
        float minDistance = calculateDistance(centroids[0], centroids[1], points[i], points[i + 1]);
        int minCluster = 0;
        for (int j = 2; j + 1 < K * 2; j += 2)
        {
            float newDistance = calculateDistance(centroids[j], centroids[j + 1], points[i], points[i + 1]);
            if (newDistance < minDistance)
            {
                minDistance = newDistance;
                minCluster = j / 2;
            }
        }

        points[i + 2] = minCluster;
        sum[minCluster * 2] += points[i];
        sum[minCluster * 2 + 1] += points[i + 1];
        num_elems[minCluster]++;
    }
}
