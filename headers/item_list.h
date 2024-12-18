#ifndef ITEM_LIST_H
#define ITEM_LIST_H

#include "./item.h"

typedef struct Item_list Item_list;

struct Item_list{

    int number_of_item_list; // start with 0

    Item *item_list_head; // start with NULL
    Item *item_list_tail; // start with NULL

};

// add item to itemList and return item which added
Item *add_items_list(Item_list *itemList);

// Processes what it reads from the “items.txt” file
// içinde *add_items_list fonksiyonunu çağırır, düğüm eklemek için
void load_item_infos(Item_list *itemList);

void display_item_list(Item_list *itemList);

// if can't find return NULL
Item* find_item_itemList(int itemId, Item_list *itemList);

#endif // ITEM_LIST_H