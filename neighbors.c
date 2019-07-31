#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "neighbors.h"

void gen_neighbor_set_unseeded(neighbor *neighbor_array_start, int number, int size_x, int size_y, int size_z)
{
    for(int n = 0; n < number; ++n) {
        neighbor_array_start[n].x = (random() % size_x);
        neighbor_array_start[n].y = (random() % size_y);
        if(size_z != -1) // Let graphs be 2d by giving -1 as a flag value
            neighbor_array_start[n].z = (random() % size_z);
        else
            neighbor_array_start[n].z = -1;
    }
    
}

void gen_neighbor_set(neighbor *neighbor_array_start, int number, int size_x, int size_y, int size_z)
{
    srand(time(NULL));
    gen_neighbor_set_unseeded(neighbor_array_start, number, size_x, size_y, size_z);
}

distance get_neighbor_distance_allvals(neighbor na, neighbor nb)
{
    distance d;
    d.x = abs(na.x - nb.x);
    d.y = abs(na.y - nb.y);
    if(na.z == -1 || nb.z == -1) {
        d.c = sqrt(d.x*d.x + d.y*d.y);
    } else {
        d.z = abs(na.z - nb.z);
        d.c = sqrt(sqrt(d.x*d.x + d.y*d.y)*sqrt(d.x*d.x + d.y*d.y));
    }

    return d;
}

distance get_neighbor_distance_allvals_by_index(neighbor *neighbor_array_start, int index_a, int index_b)
{
    return get_neighbor_distance_allvals(neighbor_array_start[index_a], neighbor_array_start[index_b]);
}

bool closerthan(distance a, distance b)
{
    return a.c <= b.c;
}

float get_neighbor_distance(neighbor na, neighbor nb)
{
    return (get_neighbor_distance_allvals(na, nb)).c;
}

float get_neighbor_distance_by_index(neighbor *neighbor_array_start, int index_a, int index_b)
{
    return (get_neighbor_distance_allvals(neighbor_array_start[index_a], neighbor_array_start[index_b])).c;
}

void draw_neighbors(neighbor *neighbor_array_start, int count, int size_x, int size_y, char *filepath)
{

}

void print_neighbors(neighbor *neighbor_array_start, int count)
{
    printf("X, Y, Z values for %d neighbors\n", count);
    for(int n = 0; n < count; ++n)
        printf("%3d: [%5d, %5d, %5d]\n", n, neighbor_array_start[n].x, neighbor_array_start[n].y, neighbor_array_start[n].z);
}


