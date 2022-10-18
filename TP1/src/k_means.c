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
    printf("hiiiiiii");

    /*
    while(notOver){
        if(count == 0){
            // Se for a primeira iteração, não é preciso calcular o centróide.
            for(int p = 0; p < N; p++){
                addToClosestCluster(points[p],clusters,K);
            }
        } else {
            int allEqual = 0;
            struct cluster* temp = (struct cluster*)malloc(sizeof(struct cluster));
            for(int i = 0; i < K; i++){
                temp = clusters[i];
                findCentroid(clusters[i]);
                if(temp->centroid[0] == clusters[i]->centroid[0] && temp->centroid[1] == clusters[i]->centroid[1]){
                    allEqual++;
                }
            }
            free(temp);
            if(allEqual == K) notOver = FALSE;
            else{
                for(int p = 0; p < N; p++){
                    addToClosestCluster(points[p],clusters,K);
                }
            }
        }
        count++;
    }

    for(int i = 0; i < K; i++){
        printf("Cluster --> %d: \n",i);
        printf("Coordinate X: %f\n",clusters[i]->x);
        printf("Coordinate Y: %f\n\n",clusters[i]->y);
    }
    ----------------------------------------- OUTPUT DO PROGRAMA:
    printf("N = %d, K = %d\n",N,K);
    for(int i = 0; i < K; i++){
        printf("Center: (%f, %f) : Size: %d\n",clusters[i]->centroid[0], clusters[i]->centroid[1], clusters[i]->number_points);
    }
    printf("Interations: %d\n",count);
    */
    free_structs(N,K,points,clusters);
    return 0;
}