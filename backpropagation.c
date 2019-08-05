#include "backpropagation.h"

const float etha = 0.1;

// Verify if in previous number of steps network is null or not
bool verify_prev_steps(network *current, int steps)
{
    for(int i = 0; i <= steps; i++)
    {
        if(current == NULL)
            return false;

        current = current->prev;
    }

    return true;
}

// Copy container in another one
container cpy_container(container current)
{
    container curr_dubl = init_array(current.array.width);

    for(int i = 0; i < current.array.width; i++)
        curr_dubl.array.arr[i] = current.array.arr[i];

    return curr_dubl;
}

void network_backpropagation(network **curr_network, int position)
{
    // Verify if network is null
    isnull(*curr_network, "Backpropagation");

    // If we aren't on the end of list,
    // then go to tale
    if((*curr_network)->next != NULL)
        to_tale(curr_network);

    network *current = *curr_network;

              // Extract output
    container scnd_layer = current->current,
              // Previous layer and his dublicate
              frst_layer, frst_layer_dubl,
              weights;

    double deriv_error;

    // Calculate error's derivate
    for(int i = 0; i < outputs.width; i++)
        deriv_error += deriv_E(outputs.matrix[position][i],
                               scnd_layer.array.arr[i]);

    while(verify_prev_steps(current, 2))
    {
        // Extract second layer and weight
        // to calculate the previous (first) layer.
        //-----------------------------------------
        scnd_layer = current->current;
        weights    = current->prev->current;

        current    = current->prev->prev;

        frst_layer = current->current;
        frst_layer_dubl = cpy_container(frst_layer);
        //-----------------------------------------

        // Recalculate first layer without inputs
        //----------------------------------------
        if(current->prev != NULL)
            recalc_layer(frst_layer, weights,
                         scnd_layer, deriv_error);
        //----------------------------------------

        // Make error's derivate 1
        // Used just for last hidden layer
        deriv_error = 1;

        // Recalculate weight
        recalc_weight(frst_layer_dubl, weights,
                      scnd_layer);
    }

    // Save the head's list position
    *curr_network = current;
}

void to_tale(network **network)
{
    // Go to the end of the list
    while((*network)->next != NULL)
            (*network) = (*network)->next;
}

double deriv_sigmoid(double output)
{
    return output*(1 - output);
}

void recalc_layer(container frst_layer, container weights,
                  container scnd_layer, double deriv_error)
{
    // Recalculate every cell from layer
    for(int i = 0; i < frst_layer.array.width; i++)
    {
        frst_layer.array.arr[i] = 0;
        for(int j = 0; j < scnd_layer.array.width; j++)
            frst_layer.array.arr[i] += weights.matrix.matrix[i][j] *
                                       deriv_sigmoid(scnd_layer.array.arr[j]) *
                                       deriv_error;
    }
}

void recalc_weight(container frst_layer, container weights,
                   container scnd_layer)
{
    // Recalculate every cell from width
    for(int i = 0; i < weights.matrix.height; i++)
        for(int j = 0; j < weights.matrix.width; j++)
            weights.matrix.matrix[i][j] += deriv_sigmoid(frst_layer.array.arr[i]) *
                                           scnd_layer.array.arr[i] * etha;
}
