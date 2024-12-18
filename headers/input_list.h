#ifndef INPUT_LIST_H
#define INPUT_LIST_H

#include "./input.h"

typedef struct Input_list Input_list;

// For to be able to record the user's progress
struct Input_list{

    int number_of_input_list; // start with 0

    Input *input_list_head; // start with NULL
    Input *input_list_tail; // start with NULL

};

// Adds the inputs entered by the user to the list
void add_input(int input, Input_list *myInputs);

#endif // INPUT_LIST_H 