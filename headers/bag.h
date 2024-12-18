#ifndef BAG_H
#define BAG_H

#include "./item_list.h"

typedef struct Bag Bag;

struct Bag{

    int number_of_item_bag; // start with 0
    int bag_limit; // start with (int x) bag capacityre

    Item *bag_head; // start with NULL
    Item *bag_tail; // start with NULL

};

void add_item_bag(
    Bag *myBag,
    int item_id,
    char item_name[10],
    int health_change,
    int damage_up,
    int shield_up);

void remove_item_bag(Bag *myBag, int item_id);

void display_bag(Bag *myBag);

// if can't find return NULL
Item* find_item_bag(int itemId, Bag *myBag);

#endif // BAG_H