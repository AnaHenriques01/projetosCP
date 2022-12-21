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
    int startIndex, minCluster, numElems;
    float minDistance, newDistance;

    // Cálculo dos novos centróides e restauração do valor sum e do número de elementos de cada cluster
    if (iteration > 0)
    {
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

    // Atribuir um valor para o índice de partida consoante a iteração atual
    if (iteration == 0)
        startIndex = K;
    else
        startIndex = 0;

    // Initialize MPI variables
    int num_procs, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Calculate the portion of the loop each process should handle
    int portion = (N * 3 - startIndex * 3) / num_procs;
    int start = startIndex * 3 + portion * rank;
    int end = start + portion;

    if (rank == num_procs - 1)
    {
        end = N * 3;
    }
    // Iterate over the portion of the loop assigned to this process
    for (int i = start; i < end; i += 3)
    {
        // Find the closest cluster based on its centroid
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

        // Assign the point to the closest cluster and update the sum and number of elements for each cluster
        points[i + 2] = minCluster;
        sum[minCluster * 2] += points[i];
        sum[minCluster * 2 + 1] += points[i + 1];
        num_elems[minCluster]++;
    }

    // Gather the sum and num_elems arrays from all processes into a single array on the root process
    float global_sum[K * 2];
    int global_num_elems[K];
    MPI_Reduce(sum, global_sum, K * 2, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(num_elems, global_num_elems, K, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // If this is the root process, update the centroids based on the global sum and num_elems arrays
    if (rank == 0)
    {
        for (int j = 0; j + 1 < K * 2; j += 2)
        {
            numElems = global_num_elems[j / 2];
            centroids[j] = global_sum[j] / numElems;
            centroids[j + 1] = global_sum[j + 1] / numElems;
        }
    }
}
