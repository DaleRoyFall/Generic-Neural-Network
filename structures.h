#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

// Container with (array or matrix) class
// and a interface with free method
//---------------------------------
typedef struct container container;

typedef struct
{
    void (*free)(container);
}interface;

typedef struct
{
    int     width;
    double *arr;
}array;

typedef struct
{
    int      width;
    int      height;
    double **matrix;
}matrix;

typedef struct container
{
    interface imethod;
    union
    {
        array  array;
        matrix matrix;
    };
}container;
//---------------------------------

// Double linked list of containers
//---------------------------------
typedef struct network network;

typedef struct network
{
    container current;
    network *prev;
    network *next;
}network;
//---------------------------------

// Pattern function
// Used to extract structure from file
// Like inputs, outputs and pattern
//------------------------------------
typedef struct
{
    int height;
    int width;
    int **matrix;

    interface imethod;
}pattern;
//------------------------------------

#endif
