#include "neighbors.h"
#include <stdio.h>

// I'm defining these to avoid having them be magic numbers.
// 'conts ints' would work just as well
#define neighborcount  3000
#define neighborhood_x 100
#define neighborhood_y 100
#define neighborhood_z -1

int main(void) {
    // The set of neighbors is just an array of the 'neighbor' type.
    neighbor narray[neighborcount];

    // gen_neighbor_set creates a random set of neighbors within the x, y, z space provided.
    // Note that, for debug purposes, I'm using the 'unseeded' version of this function: it will
    // produce the same values every run. For random values, use 'gen_neighbor_set' with the same parameters.
    //
    // The other thing I'm doing for debug purposes is setting 'z' to -1. All neighbors are in the positive
    // space, so this is a flag value that sets us to be 2d. This is useful when using the 'draw_neighbors'
    // function, which turns the neighbors array into an image. For actual usage, make neighborhood_z be not -1
    // and the code should otherwise function the same way.
    gen_neighbor_set_unseeded(narray, neighborcount, neighborhood_x, neighborhood_y, neighborhood_z);

    // Again, nice for debug to see what you're dealing with.
    print_neighbors(narray, neighborcount);

    // We're going to find the nearest neighbor to the 0th element. So, save that and start checking from 1.
    neighbor first = narray[0];
    neighbor nearest = narray[1];
    neighbor current;
    float  closest = neighborhood_x*neighborhood_y; // Set the current to the max possible distance
    for(int n = 1; n < 30; ++n) {
        current = narray[n];
        float d;
        d = get_neighbor_distance(first, current);
        if(d < closest) {
            nearest = current;
            closest = d;
        }
    }

    printf("The nearest neighbor I found: \n[%5d, %5d, %5d] (%.3f away)\n", nearest.x, nearest.y, nearest.z, closest);

    return 0;
}
