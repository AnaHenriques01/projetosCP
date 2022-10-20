#ifndef __UTILS_H
#define __UTILS_H

struct cluster{
    float* centroid;    // [1.2, 3.8] = centroid
    float** points;     // [ [1.2, 3.8], [9.2, 24.1], [3.5, 12.9] ] ---> 3 points
    int number_points;  // 3
    int max_points;     // 30
};

float** initPoints(int N);

struct cluster** initClusters(int N, int K);

void init(int N, int K, float** points, struct cluster** clusters);

void addToPoints(struct cluster* cluster, float* point);

void addToClosestClusterInit(int K, int N, float** points, struct cluster** clusters);

void addToClosestCluster(int K, struct cluster** clusters);

void findCentroid(struct cluster* cluster);

void free_points(int N, float** points);

void free_clusters(int K, struct cluster** clusters);

void free_structs(int N, int K, float** points, struct cluster** clusters);

#endif