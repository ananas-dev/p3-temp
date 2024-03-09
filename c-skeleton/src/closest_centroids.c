#include "../headers/closest_centroids.h"
#include "../headers/point.h"
#include "../headers/distance.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int closest_centroid(point_t* centroids, point_t *points, int k, int num_points, squared_distance_func_t squared_distance_function){

    // Check for parameter and return -1 if there is a wrong parameter
    if(centroids == NULL || points == NULL || k < 0 || num_points < 0 || squared_distance_function == NULL) {
        return -1;
    }

    int changed = 0;
    
    for(int i = 0; i < num_points; i++) {   // For each point
        const point_t *p = &points[i];
        uint32_t oldClusterID = p->clusterID;  // Remember the old centroid to know if it has changed
        int64_t minDistance = INT64_MAX;

        for(int clusterIndex = 0; clusterIndex < k; clusterIndex++) {   // For each centroid
            const point_t *c = &centroids[clusterIndex];
            int64_t dist = squared_distance_function(p, c); // Compute the distance between the current point and current centroid

            if(dist < minDistance) {    // Update point clusterID if it's closer 
                p->clusterID = clusterIndex;
                minDistance = dist;
                if(clusterIndex != oldClusterID) {
                    changed = 1;
                }
            }
        }
    }

    return changed;
}