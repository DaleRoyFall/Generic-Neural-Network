#include "array.h"
#include "libraries.h"

/* This file is used to work with the array.
   It contains all the subroutines that are attributed to arrays. */

// Allocate memory and initialize the array structure
container init_array(int width)
{
    // Initialize matrix
    //-------------------------------------------
    double *arr = malloc(sizeof(double) * width);

    srand(time(NULL));
    for(int i = 0; i < width; i++)
        arr[i] = 0;
    //-------------------------------------------

     // Initialize array structure
     //--------------------------------------
    array curr_arr = (array) {width = width,
                              arr   = arr};
    //-------------------------------------

    // Initialize container
    //-----------------------------------------------------
    container current = (container) {.imethod = free_array,
                                     .array   = curr_arr};
    //-----------------------------------------------------

    return current;
}

// Free container's memory
void free_array(container current)
{
    free(current.array.arr);
}
