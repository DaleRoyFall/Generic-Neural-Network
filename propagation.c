#include "propagation.h"

void isnull(network *network, char *name_func)
{
    if(network == NULL)
    {
        printf("%s gets a null network!", name_func);
        abort();
    }
}

bool verify_next_steps(network *current, int steps)
{
    for(int i = 0; i <= steps; i++)
    {
        if(current == NULL)
            return false;

        current = current->next;
    }

    return true;
}

void to_head(network **network)
{
    // Go to the start of the list
    while((*network)->prev != NULL)
            (*network) = (*network)->prev;
}

void calc_layer(container frst_layer, container weights,
                container scnd_layer)
{
    // Calculate hidden layer
    for(int i = 0; i < scnd_layer.array.width; i++)
    {
        scnd_layer.array.arr[i] = 0;

        // Calculate sum between all weight and inputs who touch
        // concrete element from hidden layer
        for(int j = 0; j < frst_layer.array.width; j++)
            scnd_layer.array.arr[i] += frst_layer.array.arr[j] *
                                         weights.matrix.matrix[j][i];

        // Calculate output of hidden layer
        scnd_layer.array.arr[i] = sigmoid(scnd_layer.array.arr[i]);
    }
}

void network_propagation(network **curr_network)
{
    // Verify if network is null
    isnull(*curr_network, "Propagation");

    // If we aren't on the start of list,
    // then go to head
    if((*curr_network)->prev != NULL)
        to_head(curr_network);

    network *current = *curr_network;

    // First element from list is input
    container frst_layer,
              scnd_layer,
              weights;


    while(verify_next_steps(current, 2))
    {
        // Extract first layer and weight
        // to calculate the next (second) layer.
        //---------------------------------------
        frst_layer = current->current;
        weights    = current->next->current;

        current    = current->next->next;

        scnd_layer = current->current;
        //---------------------------------------

        // Calculate second layer
        calc_layer(frst_layer, weights,
                   scnd_layer);

    }

    // Save the end list's position
    *curr_network = current;
}
