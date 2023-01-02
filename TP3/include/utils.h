#ifndef __UTILS_H
#define __UTILS_H

#define N 10000000
float points[N * 3];

/**
 * @brief It inits the N points and K clusters.
 * @param K array of size N×F containing input feature vectors.
 * @param threads number of threads used.
 * @param sum Array of size K*2 containing the sum of points of each cluster.
 * @param num_elems Number of points of each cluster.
 * @param centroids Array of size K*2 containing the cluster centroids.
 */
void init(int K, float sum[K * 2], int num_elems[K], float centroids[K * 2]);

/**
 * @brief It calculates the Euclidean distance between the point and the centroid
 * @param centroidX Centroid x coordinate
 * @param centroidY Centroid y coordinate
 * @param pointX Point x coordinate
 * @param pointY Point y coordinate
 * @return The euclidean distance between the point and the centroid
 */
static inline float calculateDistance(float centroidX, float centroidY, float pointX, float pointY);

/**
 * @brief It adds the N points to their closest cluster.
 * @param iteration The loop iteration's index.
 * @param K Number of clusters in the program.
 * @param threads number of threads used.
 * @param num_elems Number of points of each cluster.
 * @param centroids Array of size K*2 containing the cluster centroids.
 * @param sum Array of size K*2 containing the sum of points of each cluster.
 * @return The number of points that didn't change of cluster.
 */
int addToClosestCluster(int iteration, int K, int num_elems[K], float centroids[K * 2], float sum[K * 2]);

#endif