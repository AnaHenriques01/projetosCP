#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "../include/utils.h"


void init(float sum[K*2], int num_elems[K], float centroids[K*2]) {

    int p, i, i2 = 0;
    srand(10);
    for(p = 0; p+2 < N*3; p+=3) {
        points[p] = (float)rand() / RAND_MAX;
        points[p+1] = (float)rand() / RAND_MAX;
        points[p+2] = -1.0;
    }
    for(i = 0; i+1 < K*2; i+=2) {
        centroids[i] = points[i2];
        centroids[i+1] = points[i2+1];
        num_elems[i/2] = 1;
        points[i2+2] = (float)i/2;
        sum[i] = points[i2];
        sum[i+1] = points[i2+1];
        i2+=3; 
    }
}


int addToClosestCluster(int count, int num_elems[K], float centroids[K*2], float sum[K*2]){
    int value, minCluster, i, j, beforeClu, numElems, allEquals = 0;
    float minDistance, newDistance, x_sum, y_sum;
    if(count == 0) value = K;
    else{
        value = 0;
        for(j = 0; j+1 < K*2; j+=2){ 
            numElems = num_elems[j/2];
            centroids[j] = sum[j]/numElems;
            centroids[j+1] = sum[j+1]/numElems;
            num_elems[j/2] = 0;
            sum[j]=0.0;
            sum[j+1]=0.0;
        }
    }
    for(i = value*3; i+2 < N*3; i+=3){
        beforeClu = points[i+2];
        minDistance = (centroids[0] - points[i])*(centroids[0] - points[i]) + (centroids[1] - points[i+1])*(centroids[1] - points[i+1]);
        minCluster = 0;
        for(j = 2; j+1 < K*2; j+=2){
            newDistance = (centroids[j] - points[i])*(centroids[j] - points[i]) + (centroids[j+1] - points[i+1])*(centroids[j+1] - points[i+1]);
            if (newDistance < minDistance){
                minDistance = newDistance;
                minCluster = j/2;
            }
        }
        sum[2*minCluster] += points[i];
        sum[(2*minCluster)+1] += points[i+1];

        if(beforeClu == minCluster) allEquals++;
        points[i+2] = minCluster;
        num_elems[minCluster]++;
    }
    return allEquals;
}