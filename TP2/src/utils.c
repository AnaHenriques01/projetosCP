#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#include "../include/utils.h"

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

// acrescentar o inline faz com que apenas seja aplicada a função e não que chame a função
// do que me lembro isto não mexe praticamente com o tempo
// foi mais para a legibilidade do código
static inline float calculateDistance(float centroidX, float centroidY, float pointX, float pointY)
{
    return (centroidX - pointX) * (centroidX - pointX) + (centroidY - pointY) * (centroidY - pointY);
}

int addToClosestCluster(int count, int K, int num_elems[K], float centroids[K * 2], float sum[K * 2])
{
    int allEquals = 0;
    int value, minCluster, beforeCluster, numElems;
    float minDistance, newDistance;

    if (count == 0)
        value = K;
    else
    {
        value = 0;
        for (int j = 0; j + 1 < K * 2; j += 2)
        {
            numElems = num_elems[j / 2];
            centroids[j] = sum[j] / numElems;
            centroids[j + 1] = sum[j + 1] / numElems;
            num_elems[j / 2] = 0;
            sum[j] = 0.0;
            sum[j + 1] = 0.0;
        }
    }

    int size_sum = K * 2;
    int size_num_elems = K;
#pragma omp parallel for reduction(+ : sum[:size_sum]) reduction(+  : num_elems[:size_num_elems])
    for (int i = value * 3; i + 2 < N * 3; i += 3)
    {
        beforeCluster = points[i + 2];
        minDistance = calculateDistance(centroids[0], centroids[1], points[i], points[i + 1]);
        minCluster = 0;
        for (int j = 2; j + 1 < K * 2; j += 2)
        {
            newDistance = calculateDistance(centroids[j], centroids[j + 1], points[i], points[i + 1]);
            if (newDistance < minDistance)
            {
                minDistance = newDistance;
                minCluster = j / 2;
            }
        }
        sum[2 * minCluster] += points[i];
        sum[(2 * minCluster) + 1] += points[i + 1];

        if (beforeCluster == minCluster)
            allEquals++;
        points[i + 2] = minCluster;
        num_elems[minCluster]++;
    }
    return allEquals;
}