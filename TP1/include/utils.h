#ifndef __UTILS_H
#define __UTILS_H

struct point{
    float x;
    float y;
};

struct cluster{
    float x;
    float y;
    float* points;
};

void init(int NP, int NC, struct point* points[NP], struct cluster* clusters[NC]);

void free_structs(int NP, int NC, struct point* points[NP], struct cluster* clusters[NC]);

#endif