#include "array.h"
#include "matrix.h"
#include "network.h"

// Used to get network's error
float const verge = 0.2;

void add_container(network **current, container curr_layer)
{
    // Allocate node and add data
    //--------------------------------------------------------
    network *new_node = malloc(sizeof(network));
             new_node->current = curr_layer;
             new_node->next = NULL;
    //--------------------------------------------------------


    network *cursor = *current;

    if(*current == NULL)
    {
        new_node->prev = NULL;
        (*current) = new_node;
    }
    else
    {
        while(cursor->next != NULL)
            cursor = cursor->next;

        cursor->next = new_node;
        new_node->prev = cursor;
    }
}

size_t verify_file(FILE *file, char *file_name)
{
    // Go to the end of the file
    fseek(file, 0, SEEK_END);

    // Verify if file exist or is empty
    if(file == NULL || !ftell(file))
    {
        printf("%s file is null or empty!", file_name);
        abort();
    }

    // Extract possible number of numbers
    size_t number = ftell(file) / 2 + 1;

    // Go to the top of the file
    rewind(file);

    return number;
}

void extract_pattern()
{
    FILE *pattern_file = fopen("pattern.txt", "r");

    // Verify if file exist or isn't empty and return
    // possible number of numbers what is contain in this file
    //--------------------------------------------------------
    size_t layers_num = verify_file(pattern_file, "Pattern");
    //--------------------------------------------------------

    // Allocate memory for array cause pattern have one line
    // (always) have one line
    //------------------------------------------------------
    int **pattern_mat = malloc(sizeof(int*) * 1);
    for(int i = 0; i < 1; i++)
        pattern_mat[i] = malloc(sizeof(int) * layers_num);
    //------------------------------------------------------

    // Extract pattern from file
    //----------------------------------------------------
    int k = 0;
    while(!feof(pattern_file))
        fscanf(pattern_file, "%d ", &pattern_mat[0][k]), k++;

    // Save network's pattern
    network_pattern = (pattern) {.height  = 1,
                                 .width   = k,
                                 .matrix  = pattern_mat,
                                 .imethod = free_matrix};

    //for(int i = 0; i < network_pattern.width; i++)
      //  printf("%d ", network_pattern.matrix[0][i]);
    //----------------------------------------------------

    fclose(pattern_file);
}

void extract_inp_out()
{
    FILE *inp_out_file = fopen("inp_out.txt", "r");

    // Verify if file exist or isn't empty, and return
    // possible number of numbers what is contain in this file
    //------------------------------------------------------------
    size_t numbers_num = verify_file(inp_out_file, "Input/Output");
    //------------------------------------------------------------

    int i = network_pattern.matrix[0][0] +
            network_pattern.matrix[0][network_pattern.width - 1];

    // Allocate memory for inputs and outputs
    //----------------------------------------------------------------------
    int **input_mat   = malloc(sizeof(int) * numbers_num),
        **outputs_mat = malloc(sizeof(int) * numbers_num);

    int inputs_width  = network_pattern.matrix[0][0],
        outputs_width = network_pattern.matrix[0][network_pattern.width - 1];

    for(int i = 0; i < numbers_num; i++)
    {
        input_mat[i]  = malloc(sizeof(int) * inputs_width);
        outputs_mat[i] = malloc(sizeof(int) * outputs_width);
    }
    //----------------------------------------------------------------------

    // Extract inputs and outputs from file
    //----------------------------------------------------
    int k = 0;
    while(!feof(inp_out_file))
    {
        // Extract inputs from every line
        for(int i = 0; i < inputs_width; i++)
            fscanf(inp_out_file, "%d ", &input_mat[k][i]);

        // Extract outputs from every line
        for(int i = 0; i < outputs_width; i++)
            fscanf(inp_out_file, "%d ", &outputs_mat[k][i]);

        k++;
    }

    // Save inputs
    inputs = (pattern) {.height  = k,
                        .width   = inputs_width,
                        .matrix  = input_mat,
                        .imethod = free_matrix};

    // Save outputs
    outputs = (pattern) {.height  = k,
                         .width   = outputs_width,
                         .matrix  = outputs_mat,
                         .imethod = free_matrix};

    /*for(int i = 0; i < inputs.height; i++)
    {
        printf("\n");

        for(int j = 0; j < inputs.width; j++)
            printf("%d ", inputs.matrix[i][j]);

        for(int j = 0; j < outputs.width; j++)
            printf("-> %d", outputs.matrix[i][j]);
    }*/
    //----------------------------------------------------

    fclose(inp_out_file);
}

network* init_list()
{
    // Current network
    network *current = NULL;

    // Layers width
    int curr_h_width,
        prev_l_width;

    // Add input
    //------------------------------------------------
    curr_h_width = network_pattern.matrix[0][0];
    add_container(&current, init_array(curr_h_width));
    prev_l_width = curr_h_width;
    //------------------------------------------------


    // Create network from network's pattern
    for(int i = 1; i < network_pattern.width; i++)
    {
        // Extract current layer's width
        curr_h_width = network_pattern.matrix[0][i];

        // Add matrix between layers
        add_container(&current, init_matrix(prev_l_width, curr_h_width));

        // Add layers
        add_container(&current, init_array(curr_h_width));

        // Save previous layer's width
        prev_l_width = curr_h_width;
    }

    return current;
}

// Get position
int get_pos(int position)
{
    // Verify inputs position
    if(position >= inputs.height)
        position %= inputs.height;

    return position;
}

void set_input(container current, int position)
{
    // Copy inputs in first container
    for(int i = 0; i < inputs.width; i++)
        current.array.arr[i] = inputs.matrix[position][i];
}

network* network_init()
{
    // Extract pattern from file
    extract_pattern();

    // Extract inputs and outputs from file
    extract_inp_out();

    // Initialize list
    return init_list();
}

// Get network's error
bool network_get_error(container current, int position)
{
    float error = 0;

    // Calculate total error from all outputs
    for(int i = 0; i < outputs.width; i++)
        error += calc_E(outputs.matrix[position][i], current.array.arr[i]);

    if(error < verge)
        return false;

    return true;
}

// Reset every layer
void reset_layer(container current)
{
    for(int i = 0; i < current.array.width; i++)
        current.array.arr[i] = 0;
}

void network_reset(network **curr_network)
{
    // Verify if network is null
    isnull(*curr_network, "Reset");

    // Go to network's head
    to_head(curr_network);

    network *current = *curr_network;

    // Reset network
    //------------------------------------
    int k = 0;
    while(current->next != NULL)
    {
        if(k % 2 == 0)
            reset_layer(current->current);

        current = current->next;

        k++;
    }
    //------------------------------------
}

// Save current pattern in file
void save_pattern()
{
    FILE *save_file = fopen("saved_pattern.txt", "w+");

    for(int i = 0; i < network_pattern.width; i++)
    {
        // Print in file every number
        fprintf(save_file, "%d", network_pattern.matrix[0][i]);

        // Print space after every number,
        // Expected the last one
        if(i != network_pattern.width - 1)
            fprintf(save_file, " ");
    }

    fclose(save_file);
}

void save_container(network *network)
{
    // Verify if network is null
    isnull(network, "Save");

    // Go to network's head
    to_head(&network);

    FILE *save = fopen("save.txt", "w+");

    // Save every weight from network
    //-------------------------------
    int k = 0;
    matrix curr_mat;

    while(network->next != NULL)
    {
        if(k % 2)
        {
            curr_mat = network->current.matrix;
            for(int i = 0; i < curr_mat.height; i++)
            {
                for(int j = 0; j < curr_mat.width; j++)
                {
                    fprintf(save, "%f", curr_mat.matrix[i][j]);
                    if(j != curr_mat.width - 1)
                        fprintf(save, " ");
                }

                fprintf(save, "\n");
            }

            fprintf(save, "\n");
        }

        network = network->next;
        k++;
    }
    //-------------------------------

    fclose(save);
}

void network_save(network *network)
{
    // Save current pattern in file
    save_pattern();

    // Save current network in file
    save_container(network);
}

void network_load()
{

}

// Print
//------------------------------------------------------
void print_network(network *network)
{
    int k = 0;

    while(network != NULL)
    {
        printf("\n");

        if(k % 2 == 0)
            print_array(network->current);
        else
            print_matrix(network->current);

        printf("\n");

        network = network->next;

        k++;
    }
}

void print_array(container current)
{
    for(int i = 0; i < current.array.width; i++)
        printf("%f\t", current.array.arr[i]);
}

void print_matrix(container current)
{
    for(int i = 0; i < current.matrix.height; i++)
    {
        printf("\n");
        for(int j = 0; j < current.matrix.width; j++)
            printf("%f\t", current.matrix.matrix[i][j]);
    }
}
//------------------------------------------------------

// Deallocate memory from container
void free_container(container current)
{
    current.imethod.free(current);
}

// Deallocate memory from all list
void free_network(network **current)
{
    to_head(current);

    network *cursor = *current,
            *next_layer;

    while(cursor->next != NULL)
    {
        next_layer = cursor->next;

        // Free each element from list
        //------------------------------
        free_container(cursor->current);
        free(cursor);
        //------------------------------

        cursor = next_layer;
    }

}
