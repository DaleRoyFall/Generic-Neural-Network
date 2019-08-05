#ifndef PROPAGATION_H_INCLUDED
#define PROPAGATION_H_INCLUDED
#include "libraries.h"
#include "network.h"

// Verify if network is null or not
void isnull(network *network, char *name_func);

// Verify if in next number of steps network is null or not
bool verify_next_steps(network *current, int steps);

// Go to the top of the list
void to_head(network **layers);

// Calculate second hidden layer using the thirst and weights
void calc_layer(container frst_layer, container weights,
                container scnd_layer);

// Leads calculations to an output
void network_propagation(network **curr_network);

#endif
