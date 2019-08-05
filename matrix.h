#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include "libraries.h"
#include "structures.h"

// Initialize matrix structure
container init_matrix(int height, int width);

// Free matrix memory
void free_matrix(container current);

#endif
