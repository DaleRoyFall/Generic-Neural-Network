#include "matrix.h"

/* This file is used to work with the matrix.
   It contains all the subroutines that are attributed to matrices. */


// Allocate memory and initialize the matrix structure
container init_matrix(int height, int width)
{
    // Initialize matrix
    //----------------------------------------------
    double **mat = malloc(sizeof(double*) * height);
    srand(time(NULL));
    for(int i = 0; i < height; i++)
    {
        mat[i] = malloc(sizeof(double) * width);
        for(int j = 0; j < width; j++)
            mat[i][j] = (double)(rand() % 101) / 100;
    }
    //----------------------------------------------

    // Initialize matrix structure
    //--------------------------------------------
    matrix curr_mat = (matrix) {.height = height,
                                .width  = width,
                                .matrix    = mat};
    //--------------------------------------------

    // Initialize container
    //------------------------------------------------------
    container current = (container) {.imethod = free_matrix,
                                     .matrix  = curr_mat};
    //------------------------------------------------------

    return current;
}

// Free container's memory
void free_matrix(container current)
{
     for(int i = 0; i < current.matrix.height; i++)
            free(current.matrix.matrix[i]);
        free(current.matrix.matrix);
}
