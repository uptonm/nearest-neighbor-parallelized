#include "neighbors.h"
#include <stdio.h>
#include <mpi.h>

#define neighborcount 30
#define neighborhood_x 100
#define neighborhood_y 100
#define neighborhood_z -1
#define comparisonNeighbor 0

int main(int argc, char **argv) {
    int numranks; int rank;
    neighbor neighborhood[neighborcount];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    gen_neighbor_set_unseeded(neighborhood, neighborcount, neighborhood_x, neighborhood_y, neighborhood_z);
    
    // if (rank == 0) 
    //     print_neighbors(neighborhood, neighborcount);

    int start = (neighborcount / numranks) * rank;
    int end = (neighborcount / numranks) * (rank + 1);

    neighbor first = neighborhood[comparisonNeighbor];
    float minDistance = (float) 99999;

    for (int i = start; i < end; i++) {
        float curDistance = get_neighbor_distance(first, neighborhood[i]);
        if (curDistance < minDistance && i != comparisonNeighbor) 
            minDistance = curDistance;
    }
    float totalMin = 0;
    MPI_Reduce(&minDistance, &totalMin, 1, MPI_FLOAT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("NeighborCount: %d, NodesUsed: %d, MinDistance: %0.6f\n", neighborcount, numranks, totalMin);
    }

    MPI_Finalize();
    return 0;
}