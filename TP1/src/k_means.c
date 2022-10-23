#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../include/utils.h"

#define N 10000000
#define K 4
#define TRUE 1
#define FALSE 0

int main(){

    printf("N = %d, K = %d\n",N,K);

    //clock_t begin = clock();

    int notOver = TRUE;
    int count = 1, allEqual;
    Point* points = (Point*)malloc(N*sizeof(Point));
    Cluster* clusters = (Cluster*)malloc(K*sizeof(Cluster));
    init(N,K,points,clusters);
    
    do{
        allEqual = addToClosestCluster(count, K, N, points, clusters);
        if(allEqual == N) notOver = FALSE;
        else count++;
    } while (notOver);

    // ----------------------------------------- OUTPUT DO PROGRAMA:
    int i;
    for(i = 0; i < K; i++){
        printf("Center: (%.3f, %.3f) : Size: %d\n",clusters[i].centroid.x, clusters[i].centroid.y, clusters[i].number_points);
    }
    printf("Interations: %d\n",count);
    // ------------------------------------------------------------

    //clock_t end = clock();
    //float time_spent = (float)(end - begin) / CLOCKS_PER_SEC;
    //printf("Elapsed: %.1f seconds\n", time_spent);

    free_structs(K, points, clusters);

    return 0;
}