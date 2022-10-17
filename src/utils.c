#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/utils.h"

void init(float **points, float **clusters, int NP, int NC) {

    // dynamic array with all the points
    points = (float**)malloc(NP*sizeof(float*));
    // dynamic array with all the clusters
    clusters = (float**)malloc(NC*sizeof(float*));

    for(int count = 0; count < 2; i++){
        // points[0] and clusters[0] represent coordinate X
        // points[1] and clusters[1] represent coordinate Y
        points[i] = (float*)malloc(2*sizeof(float));
        clusters[i] = (float*)malloc(2*sizeof(float));
    }

    srand(10);
    for(int p = 0; p < NP; p++) {
        points[p][0] = (float) rand() / RAND_MAX;       // coordinate X
        points[p][1] = (float) rand() / RAND_MAX;       // coordinate Y
    }
    for(int i = 0; i < NC; i++) {
        clusters[i][0] = points[i][0]
        clusters[i][1] = points[i][1]
    }
}
