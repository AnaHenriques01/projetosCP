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

/*
Point* initPoints(int N){
    // Point p = {0.0, 0.0};
    Point* points = (Point*)malloc(N*sizeof(Point));
    int stop = 0, num = (int)(N/2);
    for(int i = 0; i+(num-1) < N; i+=num){
        for(int j = 0; j < num; j++){
            points[i+j] = populatePoint(p);
        }
        stop = i+(num-1);
    }
    for(int i = stop+1; i < N; i++){
        points[i] = populatePoint(p);
    }
    return points;
}*/


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

Cluster populateCluster(Point c, Point* allP, int num, int max){
    Cluster clus;
    clus.centroid = populatePoint(c);
    // clus.points = (Point*)malloc(cluster.max_points*sizeof(Point));
    for(int j = 0; j < num; j++){
        clus.points[j] = populatePoint(allP[j]);
    }
    clus.number_points = num;
    clus.max_points = max;
    return clus;
}


void init(int N, int K, Point* points, Cluster* clusters) {

    clusters = initClusters(clusters,N,K);
    int stop = 0, num = (int)((N/2)+1);
    srand(10);
    for(int p = 0; p+(num-1) < N; p+=num) {
        for(int j = 0; j < num; j++){
            points[p+j].x = (float) rand() / RAND_MAX;       // coordinate X
            points[p+j].y = (float) rand() / RAND_MAX;       // coordinate Y
        }
        stop = p+num;
    }
    for(int p = stop; p < N; p++) {
        points[p].x = (float) rand() / RAND_MAX;       // coordinate X
        points[p].y = (float) rand() / RAND_MAX;       // coordinate Y
    }
    for(int i = 0; i < K; i++) {
        clusters[i].centroid.x = points[i].x;
        clusters[i].centroid.y = points[i].y;
        clusters[i] = addToPoints(clusters[i], clusters[i].centroid);
        points[i].cluster = i;
    }
/*}
    for(int i = 0; i < K; i++){
        printf("Cluster %d: (%f,%f)\n", i, clusters[i].centroid.x, clusters[i].centroid.y);
    }*/
    //clusters = addToClosestClusterInit(K,N,points,clusters);
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
    cluster.centroid.x = (float)(x_sum/cluster.number_points);
    cluster.centroid.y = (float)(y_sum/cluster.number_points);
    return cluster.centroid;
}


Cluster addToPoints(Cluster cluster, Point point){
    if(cluster.number_points+1 >= cluster.max_points)
    {
        cluster.max_points = cluster.number_points+2;
        cluster.points = realloc(cluster.points, (cluster.max_points)*sizeof(Point));
    }
    cluster.points[cluster.number_points].x = point.x;
    cluster.points[cluster.number_points].y = point.y;
    cluster.number_points = cluster.number_points+1;
    return cluster;
}

/*
Cluster removeOfPoints(int pos, Cluster cluster) {
    int stop = 0, num = (int)(cluster.number_points/2);
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
    float minDistance = euclideanDistance(clusters[0].centroid.x, clusters[0].centroid.y, p.x, p.y);
    int minCluster = 0;
    for(int i = 1; i < K; i++){
        float newDistance = euclideanDistance(clusters[i].centroid.x, clusters[i].centroid.y, p.x, p.y);
        if (newDistance < minDistance){
            minDistance = newDistance;
            minCluster = i;
        }
    }
    //addToPoints(clusters[minCluster], p);
    return minCluster;
}

/*
Cluster* addToClosestClusterInit(int K, int N, Point* points, Cluster* clusters){
    int stop = 0, minCluster, num = (int)(N/2);
    for(int i = K; i+(num-1) < N; i+=num){
        for(int j = 0; j < num; j++){
            minCluster = closestCluster(points[i+j],clusters,K);
            clusters[minCluster] = addToPoints(clusters[minCluster],points[i+j]);
        }
        stop = i+(num-1);
    }
    for(int i = stop+1; i < N; i++){
        minCluster = closestCluster(points[i],clusters,K);
        clusters[minCluster] = addToPoints(clusters[minCluster],points[i]);
    }
    for(int i = 0; i < K; i++){
        for(int j = 0; j < clusters[i].number_points; j++){
            printf("CLUSTER %d -- (%f, %f)\n",i,clusters[i].points[j].x,clusters[i].points[j].y);
        }
    }
    return clusters;
}*/

int addToClosestCluster(int count, int K, int N, Point* points, Cluster* clusters){
    /*
    for(int i = 0; i < N; i++){
        printf("point %d: (%f, %f)\n", i, points[i].x, points[i].y);
        printf("its minCluster: %d\n", points[i].cluster);
    }*/
    //printf("count: %d\n", count);
    int value, minCluster, stop = 0, num = (int)((N/2)+1), size = (int)(N/K);
    if(count == 0) value = K;
    else{
        value = 0;
        for(int i = 0; i < K; i++){
            clusters[i].centroid = findCentroid(clusters[i]);
            clusters[i].points = realloc(clusters[i].points,size*sizeof(Point));
            clusters[i].number_points = 0;
            clusters[i].max_points = size;
        }
    }
    for(int j = 0; j < K; j++){
        for(int i = 0; i < clusters[i].number_points; i++){
        }
    }
    int beforeClu, allEquals = 0;
    for(int i = value; i+(num-1) < N; i+=num){
        for(int j = 0; j < num; j++){
            beforeClu = points[i+j].cluster;
            minCluster = closestCluster(points[i+j],clusters,K);
            points[i+j].cluster = minCluster;
            clusters[minCluster] = addToPoints(clusters[minCluster],points[i+j]);
            if(beforeClu == minCluster) allEquals++;
        }
        stop = i+(num-1);
    }
    for(int i = stop+1; i < N; i++){
        beforeClu = points[i].cluster;
        minCluster = closestCluster(points[i],clusters,K);
        points[i].cluster = minCluster;
        clusters[minCluster] = addToPoints(clusters[minCluster],points[i]);
        if(beforeClu == minCluster) allEquals++;
    }/*
    for(int i = 0; i < K; i++){
    for(int p = 0; p < clusters[i].number_points; p++){
        printf("Cluster %d: (%f,%f)\n", i, clusters[i].points[p].x, clusters[i].points[p].y);
    }}
    
    for(int i = 0; i < K; i++){
        for(int j = 0; j < clusters[i].number_points; j++){
            printf("CLUSTER %d -- (%f, %f)\n",i,clusters[i].points[j].x,clusters[i].points[j].y);
        }
    }*/
    //printf("allEquals: %d\n\n",allEquals);
    return allEquals;
}

int cmpPointsOfClusters(int num_before, int num_after, Point* points_before, Point* points_after){
    if(num_before != num_after) return 0;
    else{
        for(int i = 0; i < num_before; i++){
            if(points_before[i].x != points_after[i].x || points_before[i].y != points_after[i].y) return 0;
        }
        return 1;
    }
}
/*
Cluster* addToClosestCluster(int K, Cluster* clusters){
    for(int i = 0; i < K; i++){
        int stop = 0, minCluster, num = (int)(clusters[i].number_points/2);
        for(int j = 0; j+(num-1) < clusters[i].number_points; j+=num){
            for(int k = 0; k < num; k++){
                minCluster = closestCluster(clusters[i].points[j+k],clusters,K);
                if(minCluster != i){
                    clusters[minCluster] = addToPoints(clusters[minCluster],clusters[i].points[j+k]);
                    clusters[i] = removeOfPoints(j+k, clusters[i]);
                }
            }
            stop = j+(num-1);
        }
        for(int j = stop+1; j < clusters[i].number_points; j++){
            minCluster = closestCluster(clusters[i].points[j],clusters,K);
            if(minCluster != i){
                clusters[minCluster] = addToPoints(clusters[minCluster],clusters[i].points[j]);
                clusters[i] = removeOfPoints(j, clusters[i]);
            }
        }
    }
    return clusters;
}
*/
/*
void free_points(int N, float** points){
    int stop = 0;
    for(int i = 0; i+3 < N; i+=4){
        free(points[i]);
        free(points[i+1]);
        free(points[i+2]);
        free(points[i+3]);
        stop = i+3;
    }
    for(int i = stop+1; i < N; i++){
        free(points[i]);
    }
    free(points);
}
*/

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