#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../include/utils.h"

#define N 10000000      // number of points   (NP)
#define K 4             // number of clusters (NC)
#define TRUE 1
#define FALSE 0

int main(){

    int notOver = TRUE;
    int count = 0;

    float** points = initPoints(N);
    struct cluster** clusters = initClusters(N,K);
    init(N,K,points,clusters);

    /*
    for(int i = 0; i < 5; i++){
        printf("Point %d: X is %f\n",i,points[i][0]);
        printf("Point %d: Y is %f\n\n",i,points[i][1]);
    }
    for(int i = 0; i < 2; i++){
        printf("[BEFOREEEEEEE] Cluster %d: X is %f\n",i,clusters[i]->points[0][0]);
        printf("[BEFOREEEEEEE] Cluster %d: Y is %f\n\n",i,clusters[i]->points[0][1]);
    }
    
    struct cluster* cluster = (struct cluster*)malloc(sizeof(struct cluster));
    cluster->centroid = (float*)malloc(2*sizeof(float));
    cluster->centroid[0] = 1.2;
    cluster->centroid[1] = 2.3;
    cluster->points = initPoints((int)(5/2));
    cluster->number_points = 0;
    cluster->max_points = 6;
    addToPoints(cluster,cluster->centroid);
    printf("[BEFOREEEEEEE] X is %f\n",cluster->points[0][0]);
    printf("[BEFOREEEEEEE] Y is %f\n\n",cluster->points[0][1]);
    float p[2];
    p[0] = 10.8;
    p[1] = 2.3;
    printf("[BEFORE] Centroid: (%f,%f)\n",cluster->centroid[0],cluster->centroid[1]);
    addToPoints(cluster,p);
    findCentroid(cluster);
    printf("[AFTER] Centroid: (%f,%f)\n",cluster->centroid[0],cluster->centroid[1]);
    
    addToClosestCluster(p,clusters,2);
    
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < clusters[i]->number_points; j++){
            printf("Cluster %d - Point %d: X is %f\n",i,j,clusters[i]->points[j][0]);
            printf("Cluster %d - Point %d: Y is %f\n\n",i,j,clusters[i]->points[j][1]);
        }
    }
    addToPoints(cluster,p);
    for(int i = 0; i < 6; i++){
        printf("Point %d: X is %f\n",i,cluster->points[i][0]);
        printf("Point %d: Y is %f\n\n",i,cluster->points[i][1]);
    }
    free_points(cluster->max_points,cluster->points);
    free(cluster);
    */

    
    while(notOver){
        int allEqual = 0;
        float x_before, y_before;
        for(int i = 0; i < K; i++){
            x_before = clusters[i]->centroid[0];
            y_before = clusters[i]->centroid[1];
            //printf("[BEFORE] Cluster - Centroid (%f, %f)\n",clusters[i]->centroid[0], clusters[i]->centroid[1]);
            //printf("[BEFORE] Temp - Centroid (%f, %f)\n\n",x_before, y_before);
            //printf("num: %d\n",clusters[i]->number_points);
            //printf("max: %d\n\n",clusters[i]->max_points);
            findCentroid(clusters[i]);
            if(x_before == clusters[i]->centroid[0] && y_before == clusters[i]->centroid[1]){
                allEqual++;
            }
            //printf("[AFTER] Cluster - Centroid (%f, %f)\n",clusters[i]->centroid[0], clusters[i]->centroid[1]);
            //printf("[AFTER] Temp - Centroid (%f, %f)\n\n",x_before, y_before);
        }
        if(allEqual == K) notOver = FALSE;
        else{
            addToClosestCluster(K,clusters);
        }
        printf("%d\n",count);
        count++;
    }

    // ----------------------------------------- OUTPUT DO PROGRAMA:
    printf("N = %d, K = %d\n",N,K);
    for(int i = 0; i < K; i++){
        printf("Center: (%f, %f) : Size: %d\n",clusters[i]->centroid[0], clusters[i]->centroid[1], clusters[i]->number_points);
    }
    printf("Interations: %d\n",count);
    
    free_structs(N, K, points, clusters);
    return 0;
}