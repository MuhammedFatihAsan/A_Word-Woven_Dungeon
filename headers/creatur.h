#ifndef CREATURE_H
#define CREATURE_H

/* The files that will contain this file will need these libraries,
they are all included in the innermost layer to do it separately. */
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

typedef struct Creature Creature;

struct Creature{

    int creature_id;
    int creature_health;
    int creature_damage; // must be positive

    int item_id; // The item that drops when the creature dies

    Creature *next_creature;
    Creature *prev_creature;
};

#endif // CREATURE_H