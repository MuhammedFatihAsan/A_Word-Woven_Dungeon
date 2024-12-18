#ifndef CREATURE_LIST_H
#define CREATURE_LIST_H

#include "./creatur.h"

typedef struct Creature_list Creature_list;

struct Creature_list{

    int number_of_creature_list; // start with 0

    Creature *creature_list_head; // start with NULL
    Creature *creature_list_tail; // start with NULL
};

// add creature to creatureList and return creature which added
Creature *add_creature_list(Creature_list *creatureList);

// Processes what it reads from the “creatures.txt” file
void load_creature_infos(Creature_list *creatureList);

// if can't find return NULL
Creature* find_creature_creatureList(int creatureId, Creature_list *creatureList);

#endif // CREATURE_LIST_H