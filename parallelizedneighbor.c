#include "neighbors.h"
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define neighborcount 30
#define neighborhood_x 100
#define neighborhood_y 100
#define neighborhood_z -1
#define comparisonNeighbor 0

int main(int argc, char **argv) {
    int numranks; int rank;
    float startTime; float endTime;
    float *timePerNode;
    float *timings;
    neighbor neighborhood[neighborcount];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    startTime = MPI_Wtime();

    timePerNode = (float*) malloc(numranks * sizeof(float));
    if (rank == 0) 
        timings = (float*) malloc(numranks * sizeof(float));

    gen_neighbor_set_unseeded(neighborhood, neighborcount, neighborhood_x, neighborhood_y, neighborhood_z);
    
    // if (rank == 0) 
    //     print_neighbors(neighborhood, neighborcount);

    int start = (neighborcount / numranks) * rank;
    int end = (neighborcount / numranks) * (rank + 1);

    neighbor first = neighborhood[comparisonNeighbor];
    int closestIndex;
    float minDistance = (float) 99999;

    for (int i = start; i < end; i++) {
        float curDistance = get_neighbor_distance(first, neighborhood[i]);
        if (curDistance < minDistance && i != comparisonNeighbor) {
            closestIndex = i;
            minDistance = curDistance;
        }
    }

    int *closestIndicies;
    if (rank == 0) {
        closestIndicies = (int*) malloc(numranks * sizeof(int));
    }
    // Gather each node's index of the min value
    MPI_Gather(&closestIndex, 1, MPI_INT, closestIndicies, 1, MPI_INT, 0, MPI_COMM_WORLD);

    float totalMin = 0;
    // Find the minimum distance from all the node's individual min distances
    MPI_Reduce(&minDistance, &totalMin, 1, MPI_FLOAT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        neighbor closestNeighbor;
        for (int i = 0; i < numranks; i++) {
            if (totalMin == get_neighbor_distance(first, neighborhood[closestIndicies[i]])) {
                closestNeighbor = neighborhood[closestIndicies[i]];
            }
        }
        printf("\nNeighborCount: %d, NodesUsed %d\n", neighborcount, numranks);
        printf("The nearest neighbor I found: \n[%5d, %5d, %5d] (%.3f away)\n", closestNeighbor.x, closestNeighbor.y, closestNeighbor.z, totalMin);
    }

    endTime = MPI_Wtime();
    timePerNode[rank] = endTime - startTime;

    MPI_Gather(timePerNode, 1, MPI_FLOAT, timings, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        for (int i = 0; i < numranks; i++) {
            printf("Node: %d - %0.12fs\n", i, timings[i]);
        }
    }

    MPI_Finalize();
    return 0;
}