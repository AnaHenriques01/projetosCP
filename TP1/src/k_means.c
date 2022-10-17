#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../include/utils.h"

#define N 10000000      // number of points   (NP)
#define K 4             // number of clusters (NC)

int main(){
    struct point* points[N];
    struct cluster* clusters[K];
    init(N,K,points,clusters);
    /*
    for(int i = 0; i < K; i++){
        printf("Cluster --> %d: \n",i);
        printf("Coordinate X: %f\n",clusters[i]->x);
        printf("Coordinate Y: %f\n\n",clusters[i]->y);
    }*/
    free_structs(N,K,points,clusters);
    return 0;
}