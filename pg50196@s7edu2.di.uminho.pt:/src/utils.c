#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "../include/utils.h"


Point populatePoint(Point p){
    Point point;
    point.x = p.x;    // coordinate X
    point.y = p.y;    // coordinate Y
    return point;
}


Cluster* initClusters(Cluster* clusters, int N, int K){
    int size = (int)(N/K);
    Point p = {0.0, 0.0};
    for(int i = 0; i < K; i++){
        clusters[i].centroid = populatePoint(p);
        clusters[i].points = (Point*)malloc(size*sizeof(Point));
        clusters[i].number_points = 0;
        clusters[i].max_points = size;
    }
    return clusters;
}


void init(int N, int K, Point* points, Cluster* clusters) {

    clusters = initClusters(clusters,N,K);
    int stop = 0, num = (int)((N/2)+1);
    srand(10);
    for(int p = 0; p+(num-1) < N; p+=num) {
        for(int j = 0; j < num; j++){
            points[p+j].x = (float)rand() / RAND_MAX;       // coordinate X
            points[p+j].y = (float)rand() / RAND_MAX;       // coordinate Y
        }
        stop = p+num;
    }
    for(int p = stop; p < N; p++) {
        points[p].x = (float)rand() / RAND_MAX;       // coordinate X
        points[p].y = (float)rand() / RAND_MAX;       // coordinate Y
    }
    for(int i = 0; i < K; i++) {
        clusters[i].centroid.x = points[i].x; //points[i].x;
        clusters[i].centroid.y = points[i].y; //points[i].y;
        clusters[i] = addToPoints(clusters[i], clusters[i].centroid);
        points[i].cluster = i;
    }
    addToClosestCluster(0,K,N,points,clusters);
}


float euclideanDistance(float x1, float y1, float x2, float y2){
    return (float)(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}


Point findCentroid(Cluster cluster){
    int stop = 0, num = (int)((cluster.number_points/2)+1);
    float x_sum = 0.0, y_sum = 0.0;
    for(int i = 0; i+(num-1) < cluster.number_points; i+=num){
        for(int j = 0; j < num; j++){
            x_sum += cluster.points[i+j].x;
            y_sum += cluster.points[i+j].y;
        }
        stop = i+(num-1);
    }
    for(int i = stop+1; i < cluster.number_points; i++){
        x_sum += cluster.points[i].x;
        y_sum += cluster.points[i].y;
    }
    //printf("x_sum: %f, y_sum: %f\n", x_sum, y_sum);
    cluster.centroid.x = x_sum/cluster.number_points;
    cluster.centroid.y = y_sum/cluster.number_points;
    //printf("centroid: (%f, %f)\n", cluster.centroid.x, cluster.centroid.y);
    //printf("num_elem_ %d\n\n", cluster.number_points);
    return cluster.centroid;
}


Cluster addToPoints(Cluster cluster, Point point){
    if(cluster.number_points+1 > cluster.max_points){
        cluster.max_points = cluster.number_points+2;
        cluster.points = realloc(cluster.points, (cluster.max_points)*sizeof(Point));
    }
    cluster.points[cluster.number_points].x = point.x;
    cluster.points[cluster.number_points].y = point.y;
    cluster.number_points++;
    return cluster;
}


/*
Cluster removeOfPoints(int pos, Cluster cluster) {
    int stop = 0, num = (int)((cluster.number_points/2)+1);
    for(int i = pos; i+(num-1) < cluster.number_points; i+=num){
        for(int j = 0; j < num; j++){
            cluster.points[i+j] = cluster.points[i+j+1];
        }
        stop = i+(num-1);
    }
    for(int i = stop+1; i < cluster.number_points; i++){
        cluster.points[i] = cluster.points[i+1];
    }
    cluster.number_points = cluster.number_points-1;
    return cluster;
}*/


int closestCluster(Point p, Cluster* clusters, int K){
    float minDistance = euclideanDistance(p.x, p.y, clusters[0].centroid.x, clusters[0].centroid.y);
    int minCluster = 0;
    for(int i = 1; i < K; i++){
        float newDistance = euclideanDistance(p.x, p.y, clusters[i].centroid.x, clusters[i].centroid.y);
        if (newDistance < minDistance){
            minDistance = newDistance;
            minCluster = i;
        }
    }
    return minCluster;
}


int addToClosestCluster(int count, int K, int N, Point* points, Cluster* clusters){

    int value, minCluster, stop = 0, num = (int)((N/2)+1), size = (int)(N/K);
    if(count == 0) value = K;
    else{
        value = 0;
        for(int i = 0; i < K; i++){
            clusters[i].centroid = findCentroid(clusters[i]);
            //clusters[i].points = realloc(clusters[i].points,size*sizeof(Point));
            clusters[i].number_points = 0;
            //clusters[i].max_points = size;
        }
    }
    int beforeClu, allEquals = 0;
    for(int i = value; i+(num-1) < N; i+=num){
        for(int j = 0; j < num; j++){
            beforeClu = points[i+j].cluster;
            minCluster = closestCluster(points[i+j],clusters,K);
            if(beforeClu == minCluster) allEquals++;
            points[i+j].cluster = minCluster;
            clusters[minCluster] = addToPoints(clusters[minCluster],points[i+j]);
        }
        stop = i+num;
    }
    for(int i = stop; i < N; i++){
        beforeClu = points[i].cluster;
        minCluster = closestCluster(points[i],clusters,K);
        if(beforeClu == minCluster) allEquals++;
        points[i].cluster = minCluster;
        clusters[minCluster] = addToPoints(clusters[minCluster],points[i]);
    }/*
    for(int i = 0; i < K; i++){
        for(int p = 0; p < clusters[i].number_points; p++){
            printf("Cluster %d: (%f,%f)\n", i, clusters[i].points[p].x, clusters[i].points[p].y);
        }
        printf("\n");
    }*/
    printf("allEquals %d\n\n", allEquals);
    return allEquals;
}


void free_clusters(int K, Cluster* clusters){
    for(int i = 0; i < K; i++){
        free(clusters[i].points);
    }
    free(clusters);
}


void free_structs(int K, Point* points, Cluster* clusters){
    free(points);
    free_clusters(K, clusters);
}