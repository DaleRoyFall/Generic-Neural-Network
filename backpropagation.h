#ifndef BACKPROPAGATION_H_INCLUDED
#define BACKPROPAGATION_H_INCLUDED
#include "libraries.h"
#include "structures.h"
#include "array.h"

// Return E function derivate
#define deriv_E(target, output)   (-(target - output))

// Outputs pattern
extern pattern outputs;

// Prototypes
//-----------------------------------------------------------------

// Verify if in previous number of steps network is null or not
bool verify_prev_steps(network *current, int steps);

// Copy container in another one
container cpy_container(container current);

void network_backpropagation(network **curr_network, int position);

void to_tale(network **network);

int calc_expected_output(int position);

double deriv_sigmoid(double output);

void recalc_layer(container frst_layer, container weights,
                  container scnd_layer, double deriv_error);

void recalc_weight(container frst_layer, container weights,
                   container scnd_layer);
//-----------------------------------------------------------------

#endif
