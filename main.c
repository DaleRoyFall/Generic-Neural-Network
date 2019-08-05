#include "libraries.h"
#include "array.h"
#include "matrix.h"
#include "propagation.h"
#include "network.h"

//      Pattern
// Inputs and outputs
//----------------------
pattern network_pattern;
pattern inputs;
pattern outputs;
//----------------------

int main()
{
    network *network = network_init();

    for(int i = 0; i < 1000; i++)
    {
        // Set inputs in first network's container
        set_input(network->current, get_pos(i));

        // Propagate network
        network_propagation(&network);

        // Get and compare error with verge
        // If it's true back-propagate network
        if(network_get_error(network->current, get_pos(i)))
            network_backpropagation(&network, get_pos(i));

        // Reset networks layers
        network_reset(&network);
    }

    // Print outputs
    for(int i = 0; i < 4; i++)
    {
        to_head(&network);
        set_input(network->current, get_pos(i));

        // Print inputs
        printf("(%.0f %.0f) = ", network->current.array.arr[0],
                                 network->current.array.arr[1]);


        // Propagate network
        network_propagation(&network);

        // Print outputs
        printf("%f\n", network->current.array.arr[0]);
    }

    // Extras
    // In work
    network_save(network);
    //network_load(network);

    free_network(&network);

    return 0;
}
