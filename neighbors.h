#ifndef NEIGHBORLIB
#define NEIGHBORLIB
#include <stdbool.h>





/********** STRUCTS **********/

// These structs set up the object-like behavior of everything.
// Neighbor is the actual neighbor, whose values are always positive
// and represented in x, y, and z. z can be -1 as a flag value. It's
// a point by a different name.
struct _neighbor {
    int x;
    int y;
    int z;
};
typedef struct _neighbor neighbor;

// Represents the distance between two neighbors. x is distance in the x, y
// is distance in the y, z is distance in the z, and C is the actual point-to
// -point distance as calculated by the pythagorean theorem.
struct _distance {
    float x;
    float y;
    float z;
    float c;
};
typedef struct _distance distance;

// A collection of neighbors I never ended up using, but you can if you want.
struct _neighborhood {
    neighbor *hood;
};
typedef struct _neighborhood neighborhood;





/********** Set Generation Utilities **********/

/**
* Generates a neighbor set. Note that this is unseeded (will not be random,
* making it useful for debug but not 'real life'). Give it a neighbor array
* (allocated either statically or via malloc), and the size parameters, and
* it'll do the rest.
* @param neighbor: the first element of the neighbor array.
* @param int number: The number of elements to randomly generate.
* @param int size_x: The size of the area in the x.
* @param int size_y: The size of the area in the y.
* @param int size_z: The size of the area in the z. This can be -1 for 2d areas.
*/
void gen_neighbor_set_unseeded(neighbor*, int, int, int, int);

/**
* Generates a neighbor set (this one is randomized). Give it a neighbor array
* (allocated either statically or via malloc), and the size parameters, and
* it'll do the rest.
* @param neighbor: the first element of the neighbor array.
* @param int number: The number of elements to randomly generate.
* @param int size_x: The size of the area in the x.
* @param int size_y: The size of the area in the y.
* @param int size_z: The size of the area in the z. This can be -1 for 2d areas.
*/
void gen_neighbor_set(neighbor*, int, int, int, int);





/********** Distance Utilities **********/

/**
 * Checks if the first distance is smaller than the second distance.
 * Assuming these are both distances from the relevant neighbor, that's checking
 * for which is closer. Returns 'true' if the first parameter is closer,
 * false otherwise.
 */
bool closerthan(distance, distance);

/**
 * Gets the distance between two neighbors. Returns a 'distance' object, which 
 * allows you to get all values.
 * @param neighbor na: The first neighbor to check.
 * @param neighbor nb: The second neigbor to check.
 */
distance get_neighbor_distance_allvals(neighbor, neighbor);

/**
 * Gets the distance between two neighbors by their index.
 * @param neighbor: The first element of the neighbor array.
 * @param int index_a: The index of the first item.
 * @param int index_b: The index of the second item.
 */
distance get_neighbor_distance_allvals_by_index(neighbor*, int, int);

/**
 * Calculates the distance between two neighbors. Note that the order doesn't matter,
 * as distance is always a positive number.
 */
float get_neighbor_distance(neighbor, neighbor);

/** 
 * Calculates the distance between two neighbors by index. The order still doesn't matter
 * as distance is always a positive number. 
 * @param neighbor the first element of the neighbor array
 * @param int index_a the first index
 * @param int index_b the second index
 */
float get_neighbor_distance_by_index(neighbor*, int, int);





/********** Debugging Utilities **********/

/**
 * For debugging purposes, draw the neighbors as an image. TODO, and will
 * only be capable of handling 2d images since 3d would be not helpful.
 */
void draw_neighbors(neighbor*, int, int, int, char*);

/**
 * Print out all the neighbors.
 * @param neighbor: The start of the neighbors array.
 * @param int: The number of neighbors present.
 */
void print_neighbors(neighbor*, int);

#endif
