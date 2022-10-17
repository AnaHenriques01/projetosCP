#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "../include/utils.h"

struct point* initPoint(){
    struct point* point = malloc(sizeof(struct point));
    point->x = 0.0;
    point->y = 0.0;
    return point;
}

struct cluster* initCluster(int NP){
    struct cluster* cluster = malloc(sizeof(struct cluster));
    cluster->x = 0.0;
    cluster->y = 0.0;
    cluster->points = malloc(sizeof(float)*NP);
    return cluster;
}

void init(int NP, int NC, struct point* points[NP], struct cluster* clusters[NC]) {
    for(int p = 0; p < NP; p++){
        points[p] = initPoint();
    }
    for(int i = 0; i < NC; i++){
        clusters[i] = initCluster(NP);
    }
    srand(10);
    for(int p = 0; p < NP; p++) {
        points[p]->x = (float) rand() / RAND_MAX;       // coordinate X
        points[p]->y = (float) rand() / RAND_MAX;       // coordinate Y
    }
    for(int i = 0; i < NC; i++) {
        clusters[i]->x = points[i]->x;
        clusters[i]->y = points[i]->y;
    }
}

float min(float a, float b) {
	if (a<b) return a;
    else return b;
}

// euclidean distance between two points
float euclideanDistance(float x1, float x2, float y1, float y2){
    return (float) (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void free_structs(int NP, int NC, struct point* points[NP], struct cluster* clusters[NC]){
    for(int i = 0; i < NP; i++){
        free(points[i]);
    }
    for(int i = 0; i < NC; i++){
        free(clusters[i]->points);
        free(clusters[i]);
    }
}