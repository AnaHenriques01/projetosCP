#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "../include/utils.h"


float** initPoints(int N){
    float** points = (float**)malloc(N*sizeof(float*));
    for(int i = 0; i < N; i++){
        points[i] = (float*)malloc(2*sizeof(float));
        points[i][0] = 0.0;    // coordinate X
        points[i][1] = 0.0;    // coordinate Y
    }
    return points;
}


struct cluster** initClusters(int N, int K){
    int size = (int)(N/K);
    struct cluster** clusters = (struct cluster**)malloc(K*sizeof(struct cluster*));
    for(int i = 0; i < K; i++){
        clusters[i] = (struct cluster*)malloc(sizeof(struct cluster));
        clusters[i]->centroid = (float*)malloc(2*sizeof(float));
        clusters[i]->centroid[0] = 0.0;
        clusters[i]->centroid[1] = 0.0;
        clusters[i]->points = initPoints(size);
        clusters[i]->number_points = 0;
        clusters[i]->max_points = size;
    }
    return clusters;
}


void init(int N, int K, float** points, struct cluster** clusters) {

    srand(10);
    for(int p = 0; p < N; p++) {
        points[p][0] = (float)rand() / RAND_MAX;       // coordinate X
        points[p][1] = (float)rand() / RAND_MAX;       // coordinate Y
    }
    for(int i = 0; i < K; i++) {
        clusters[i]->centroid[0] = points[i][0];
        clusters[i]->centroid[1] = points[i][1];
        addToPoints(clusters[i], clusters[i]->centroid);
    }
    addToClosestClusterInit(K,N,points,clusters);
}


float euclideanDistance(float x1, float y1, float x2, float y2){
    return (float)(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}


void findCentroid(struct cluster* cluster){
    float x_sum = 0.0, y_sum = 0.0;
    for(int i = 0; i < cluster->number_points; i++){
        x_sum += cluster->points[i][0];
        y_sum += cluster->points[i][1];
    }
    cluster->centroid[0] = (float)(x_sum/cluster->number_points);
    cluster->centroid[1] = (float)(y_sum/cluster->number_points);
}


void addToPoints(struct cluster* cluster, float* point) {
    if(cluster->number_points+1 >= cluster->max_points)
    {
        cluster->max_points = cluster->number_points+2;
        cluster->points = realloc(cluster->points, (cluster->max_points)*sizeof(float*));
        cluster->points[cluster->number_points] = (float*)malloc(2*sizeof(float));
    }
    cluster->points[cluster->number_points][0] = point[0];
    cluster->points[cluster->number_points][1] = point[1];
    cluster->number_points++;
}


void removeOfPoints(int pos, struct cluster* cluster) {
    for(int i = pos; i < cluster->number_points; i++){
        cluster->points[i] = cluster->points[i+1];
    }
    cluster->number_points = cluster->number_points-1;
}


int closestCluster(float* p, struct cluster** clusters, int K){
    float minDistance = euclideanDistance(clusters[0]->centroid[0], clusters[0]->centroid[1], p[0], p[1]);
    int minCluster = 0;
    for(int i = 1; i < K; i++){
        float newDistance = euclideanDistance(clusters[i]->centroid[0], clusters[i]->centroid[1], p[0], p[1]);
        if (newDistance < minDistance){
            minDistance = newDistance;
            minCluster = i;
        }
    }
    //addToPoints(clusters[minCluster], p);
    return minCluster;
}


void addToClosestClusterInit(int K, int N, float** points, struct cluster** clusters){
    for(int i = K; i < N; i++){
        int minCluster = closestCluster(points[i],clusters,K);
        addToPoints(clusters[minCluster],points[i]);
    }
}

void addToClosestCluster(int K, struct cluster** clusters){
    for(int i = 0; i < K; i++){
        for(int j = 0; j < clusters[i]->number_points; j++){
            int minCluster = closestCluster(clusters[i]->points[j],clusters,K);
            //printf("[CLUSTER %d] Point %d -- %d\n",i, j,minCluster);
            if(minCluster != i){
                addToPoints(clusters[minCluster],clusters[i]->points[j]);
                removeOfPoints(j, clusters[i]);
            }
        }
    }
}

/*
void free_points(int N, float** points){
    
    for(int i = 0; i < N; i++){
        free(points[i]);
    }
    free(points);
}*/


void free_clusters(int K, struct cluster** clusters){
    for(int i = 0; i < K; i++){
        free(clusters[i]->points);
        free(clusters[i]);
    }
    free(clusters);
}


void free_structs(int N, int K, float** points, struct cluster** clusters){
    free(points);
    free_clusters(K, clusters);
}