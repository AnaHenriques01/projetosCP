#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "../include/utils.h"


Cluster* initClusters(Cluster* clusters, int N, int K){
    //int size = (int)(N/K)
    int i;
    for(i = 0; i < K; i++){
        clusters[i].points = (Point*)malloc(N*sizeof(Point));
        clusters[i].number_points = 0;
        clusters[i].max_points = N;
    }
    return clusters;
}


void init(int N, int K, Point* points, Cluster* clusters) {

    clusters = initClusters(clusters,N,K);
    int p, i;
    srand(10);
    for(p = 0; p < N; p++) {
        points[p].x = (float)rand() / RAND_MAX;
        points[p].y = (float)rand() / RAND_MAX;
    }
    for(i = 0; i < K; i++) {
        clusters[i].centroid.x = points[i].x;
        clusters[i].centroid.y = points[i].y;
        clusters[i] = addToCluster(clusters[i], clusters[i].centroid);
        points[i].cluster = i;
    }
    addToClosestCluster(0,K,N,points,clusters);
}


float euclideanDistance(Point p1, Point p2){
    return (float)(sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}


Point findCentroid(Cluster cluster){
    int i;
    float x_sum = 0.0, y_sum = 0.0;
    for(i = 0; i < cluster.number_points; i++){
        x_sum += cluster.points[i].x;
        y_sum += cluster.points[i].y;
    }
    cluster.centroid.x = x_sum/cluster.number_points;
    cluster.centroid.y = y_sum/cluster.number_points;
    return cluster.centroid;
}


Cluster addToCluster(Cluster cluster, Point point){
    /*
    if(cluster.number_points+1 > cluster.max_points){
        cluster.max_points = cluster.number_points+2;
        cluster.points = realloc(cluster.points, (cluster.max_points)*sizeof(Point));
    }*/
    cluster.points[cluster.number_points].x = point.x;
    cluster.points[cluster.number_points].y = point.y;
    cluster.number_points++;
    return cluster;
}


int closestCluster(Point p, Cluster* clusters, int K){
    float minDistance = euclideanDistance(p, clusters[0].centroid);
    int minCluster = 0, i;
    for(i = 1; i < K; i++){
        float newDistance = euclideanDistance(p, clusters[i].centroid);
        if (newDistance < minDistance){
            minDistance = newDistance;
            minCluster = i;
        }
    }
    return minCluster;
}


int addToClosestCluster(int count, int K, int N, Point* points, Cluster* clusters){

    int value, minCluster, i; //size = (int)(N/K), i;
    if(count == 0) value = K;
    else{
        value = 0;
        for(i = 0; i < K; i++){
            clusters[i].centroid = findCentroid(clusters[i]);
            //clusters[i].points = realloc(clusters[i].points,size*sizeof(Point));
            clusters[i].number_points = 0;
            //clusters[i].max_points = N;
        }
    }
    int beforeClu, allEquals = 0;
    for(i = value; i < N; i++){
        beforeClu = points[i].cluster;
        minCluster = closestCluster(points[i],clusters,K);
        if(beforeClu == minCluster) allEquals++;
        points[i].cluster = minCluster;
        clusters[minCluster] = addToCluster(clusters[minCluster],points[i]);
    }
    return allEquals;
}


void free_clusters(int K, Cluster* clusters){
    int i;
    for(i = 0; i < K; i++){
        free(clusters[i].points);
    }
    free(clusters);
}


void free_structs(int K, Point* points, Cluster* clusters){
    free(points);
    free_clusters(K, clusters);
}