#ifndef ITEMS_H
#define ITEMS_H

/* The files that will contain this file will need these libraries,
they are all included in the innermost layer to do it separately. */
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

typedef struct Item Item;

struct Item{

    int item_id;
    char item_name[10];

    int health_change; // It can be increased or decreased health (it can be negative)
    int damage_up; // must be positive
    int shield_up; // must be positive

    Item *next_item;
    Item *prev_item;
};

#endif // ITEMS_H