#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED
#include "libraries.h"
#include "structures.h"

//      Pattern
// Inputs and outputs
//----------------------
extern pattern network_pattern,
               inputs, outputs;
//----------------------

// Return sigmoid function
#define sigmoid(num)              (1/(1 + exp(-num)))
// Return E function
#define calc_E(target, output)    (0.5 * pow(target - output, 2))

// Prototypes
//----------------------------------------------------------
size_t verify_file(FILE *file, char *file_name);

void extract_pattern();

void extract_inp_out();

void add_container(network **current, container curr_layer);

network* init_list();

// Get position
int get_pos(int position);

void set_input(container current, int position);

network* network_init();

// Get network's error
bool network_get_error(container current, int position);

// Reset every layer
void reset_layer(container current);

void network_reset(network **curr_network);

// Save current pattern in file
void save_pattern();

void save_container(network *network);

void network_save(network *network);
void network_load();
//----------------------------------------------------------

// Print network
//------------------------------------------------------
void print_network(network *network);
void print_array(container current);
void print_matrix(container current);
//------------------------------------------------------

// Free container's memory
//-------------------------------------

// Deallocate memory from container
void free_container(container current);

// Deallocate memory from all list
void free_network(network **network);
//-------------------------------------

#endif
