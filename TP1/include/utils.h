#ifndef __UTILS_H
#define __UTILS_H

/**
 *  @struct point
 *  @brief It represents a 2D point.
 */
typedef struct point{
    float x;              /** Coordinate X */
    float y;              /** Coordinate Y */
    int cluster;          /** Point's Cluster */
} Point;


/**
 *  @struct cluster
 *  @brief It represents a cluster.
 */
typedef struct cluster{
    Point centroid;       /** Cluster's Centroid */
    Point* points;        /** Cluster's Points */
    int number_points;    /** Number of Points */
    int max_points;       /** Maximum of Points */
} Cluster;


/**
 * @brief It populates a point's coordinates X and Y.
 * @param point The point whose coordinates will be used to populate another.
 * @return A new populated point.
 */
Point populatePoint(Point point);


/**
 * @brief It inits the K clusters.
 * @param clusters The K clusters.
 * @param N Number of points in the program.
 * @param K Number of clusters in the program.
 * @return The K clusters initialized.
 */
Cluster* initClusters(Cluster* clusters, int N, int K);


/**
 * @brief It inits the N points and K clusters.
 * @param N Number of points in the program.
 * @param K Number of clusters in the program.
 * @param clusters The N points.
 * @param clusters The K clusters.
 */
void init(int N, int K, Point* points, Cluster* clusters);


/**
 * @brief It calculates the euclidean distance between two points.
 * @param p1 A point.
 * @param p2 A point.
 * @return Euclidean Distance between two points.
 */
float euclideanDistance(Point p1, Point p2);


/**
 * @brief It calculates the centroid of a given cluster.
 * @param cluster The cluster whose centroid is to be calculated.
 * @return The centroid.
 */
Point findCentroid(Cluster cluster);


/**
 * @brief It adds a point to a cluster.
 * @param cluster The cluster to where the point will be added.
 * @param point The point to be added.
 * @return The cluster with the new point.
 */
Cluster addToCluster(Cluster cluster, Point point);


/**
 * @brief It finds the closest cluster to a given point.
 * @param point A point.
 * @param clusters The K clusters.
 * @param K Number of clusters in the program.
 * @return The index of the closest cluster to a given point.
 */
int closestCluster(Point p, Cluster* clusters, int K);


/**
 * @brief It adds the N points to their closest cluster.
 * @param count The loop iteration's index.
 * @param K Number of clusters in the program.
 * @param N Number of points in the program.
 * @param points The N points.
 * @param clusters The K clusters.
 * @return The number of points that didn't change of cluster.
 */
int addToClosestCluster(int count, int K, int N, Point* points, Cluster* clusters);


/**
 * @brief It deallocates the memory previously allocated for the K clusters.
 * @param K Number of clusters in the program.
 * @param clusters The K clusters.
 */
void free_clusters(int K, Cluster* clusters);


/**
 * @brief It deallocates the memory previously allocated for the N points and the K clusters.
 * @param K Number of clusters in the program.
 * @param points The N points.
 * @param clusters The K clusters.
 */
void free_structs(int K, Point* points, Cluster* clusters);

#endif