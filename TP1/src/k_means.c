#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../include/utils.h"

#define N 10000000      // number of points   (NP)
#define K 4        // number of clusters (NC)
#define TRUE 1
#define FALSE 0

int main(){

    printf("N = %d, K = %d\n",N,K);

    int notOver = TRUE;
    int count = 0, allEqual;
    Point* points = (Point*)malloc(N*sizeof(Point));    // [[x,y], [x,y], [x,y]]
    Cluster* clusters = (Cluster*)malloc(K*sizeof(Cluster));
    init(N,K,points,clusters);

    do{
        allEqual = addToClosestCluster(count, K, N, points, clusters);
        if(allEqual == N) notOver = FALSE;
        count++;
    } while (notOver);

    // ----------------------------------------- OUTPUT DO PROGRAMA:
    for(int i = 0; i < K; i++){
        printf("Center: (%.2f, %.2f) : Size: %d\n",clusters[i].centroid.x, clusters[i].centroid.y, clusters[i].number_points);
    }
    printf("Interations: %d\n",count-1);
    // ------------------------------------------------------------

    free_structs(K, points, clusters);
    return 0;
}