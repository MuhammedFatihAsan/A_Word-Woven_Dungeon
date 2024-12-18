#include "../headers/input_list.h"

void add_input(int input, Input_list *myInputs)
{

    Input *new_input = (Input *)malloc(sizeof(Input));

    // if malloc fail
    if (new_input == NULL) {
        printf("Failed to allocate memory.\n");
        return;
    }

    if(myInputs->number_of_input_list == 0)
    {
        myInputs->input_list_head = new_input;
        myInputs->input_list_tail = new_input;
        new_input->nxt_input = NULL; // for safety
        new_input->prv_input = NULL; // for safety
        myInputs->number_of_input_list++;
    }
    else
    {
        myInputs->input_list_tail->nxt_input = new_input;
        new_input->prv_input = myInputs->input_list_tail;
        myInputs->input_list_tail = new_input;
        new_input->nxt_input = NULL; // for safety
        myInputs->number_of_input_list++;
    }

    new_input->input = input;

}