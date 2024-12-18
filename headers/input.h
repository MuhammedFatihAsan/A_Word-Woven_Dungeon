#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Input Input;

struct Input{

    int input;
    Input *nxt_input;
    Input *prv_input;

};


#endif // INPUT_H 