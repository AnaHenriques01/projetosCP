#ifndef __UTILS_H
#define __UTILS_H

struct cluster{
    float* centroid;    // [1.2,3.8] = centroid
    float** points;     // [ [1.2,3.8], [9.2,24.1], [3.5,12.9] ] ---> 3 points
    int number_points;  // 3
    int max_points;     // 30
};

float** initPoints(int NP);

struct cluster** initClusters(int NP, int NC);

void init(int NP, int NC, float** points, struct cluster** clusters);

void addToPoints(struct cluster* cluster, float* point);

void addToClosestCluster(float* p, struct cluster** clusters, int NC);

void findCentroid(struct cluster* cluster);

void free_structs(int NP, int NC, float** points, struct cluster** clusters);

#endif