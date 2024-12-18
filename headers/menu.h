#ifndef MENU_H
#define MENU_H

#include "./player.h"
#include <dirent.h> // Required for reading indexes

void save(Input_list *myInputs, char save_name[11]);

void list_saved_files();

// Processes incoming saved inputs in order
void upload_progress(
    Input_list *myInputs,
    Item_list *itemList,
    Creature_list *creatureList,
    Map *myMap,
    Bag *myBag,
    Player *myPlayer);

/* The file name to be uploaded should be taken
without typing the .txt extension*/
void load_the_save(
    char file_name[11],
    Item_list *itemList,
    Creature_list *creatureList,
    Input_list *myInputs,
    Map *myMap,
    Bag *myBag,
    Player *myPlayer);

// free the Item_list
void free_item_list(Item_list *itemList);

// free the Input_list
void free_input_list(Input_list *myInputs);

// free the bag
void free_bag(Bag *myBag);

// free the Creature_list
void free_creature_list(Creature_list *creatureList);

// free the map
void free_map(Map *myMap);

// for save load
// added input_cursor
void take_to_hand_load_version(
    int itemId,
    Player *myPlayer,
    Bag *myBag,
    Item_list *itemList,
    int cursor_input);

// for save load
// added input_cursor
void creature_fight_load_version(
    Player *myPlayer, 
    Creature_list *creatureList,
    Map *myMap,
    Bag *myBag,
    int cursor_input);

#endif // MENU_H