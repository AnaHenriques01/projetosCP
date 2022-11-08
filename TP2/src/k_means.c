#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../include/utils.h"


int main(int argc, char *argv[]){

    int notOver = 1;
    int count = 1, allEquals;
    int K = 4/*atoi(argv[2])*/, threads = 2/*atoi(argv[3])*/;
    float sum[K*2];
    int num_elems[K];
    float centroids[K*2];

    printf("N = %d, K = %d\n",N,K);

    init(K, threads, sum, num_elems, centroids);
    addToClosestCluster(0, K, threads, num_elems, centroids, sum);

    if(N <= K) notOver = 0;   // BEST CASE
    do{
        allEquals = addToClosestCluster(count, K, threads, num_elems, centroids, sum);
        if(allEquals == N) notOver = 0;
        else count++;
    } while (notOver);

    // ----------------------------------------- OUTPUT DO PROGRAMA:
    int i, i2 = 0;
    for(i = 0; i+1 < K*2; i+=2){
        printf("Center: (%.3f, %.3f) : Size: %d\n",centroids[i], centroids[i+1], num_elems[i2], sum);
        i2++;
    }
    printf("Interations: %d\n",count);
    // ------------------------------------------------------------

    return 0;
}