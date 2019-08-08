#include "neighbors.h"
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define neighborcount 500000
#define neighborhood_x 10000
#define neighborhood_y 10000
#define neighborhood_z 10000
#define comparisonNeighbor 0

int main(int argc, char **argv) {
    int numranks; int rank;
    neighbor neighborhood[neighborcount];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    gen_neighbor_set_unseeded(neighborhood, neighborcount, neighborhood_x, neighborhood_y, neighborhood_z);
    
    int start = (neighborcount / numranks) * rank;
    int end = (neighborcount / numranks) * (rank + 1);

    neighbor first = neighborhood[comparisonNeighbor];
    int closestIndex;
    double minDistance = (double) 99999;

    for (int i = start; i < end; i++) {
        double curDistance = get_neighbor_distance(first, neighborhood[i]);
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

    double totalMin = 0;
    // Find the minimum distance from all the node's individual min distances
    MPI_Reduce(&minDistance, &totalMin, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);

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

    MPI_Finalize();
    return 0;
}