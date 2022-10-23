#ifndef __UTILS_H
#define __UTILS_H

typedef struct point{
    float x;
    float y;
    int cluster;
} Point;

typedef struct cluster{
    Point centroid;   // [x,y]
    Point* points;    // [[x,y], [x,y], [x,y], ..., ...]
    int number_points; // 3
    int max_points;    // 5 -- 2 vazios
} Cluster;


Point populatePoint(Point point);

Cluster* initClusters(Cluster* clusters, int N, int K);

Cluster* populateClusters(int K, Cluster* clusters);

void init(int N, int K, Point* points, Cluster* clusters);

Cluster addToPoints(Cluster cluster, Point point) ;

// Cluster* addToClosestClusterInit(int K, int N, Point* points, Cluster* clusters);

int addToClosestCluster(int count, int K, int N, Point* points, Cluster* clusters);

Point findCentroid(Cluster cluster);

void free_clusters(int K, Cluster* clusters);

void free_structs(int K, Point* points, Cluster* clusters);

#endif