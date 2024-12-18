#ifndef PLAYER_H
#define PLAYER_H

#include "./map.h"
#include "./bag.h"
#include "./input_list.h"

typedef struct Player Player;

struct Player{

    int player_hp; // start with 100
    int player_atack_power; // start with 10
    int player_shield_power; // start with 0

    int key_count;
    int key_check[3];
    
    Item *player_right_hand; //!!! start with NULL
    Item *player_left_hand; // !!! start with NULL

    Room *player_location; // !!! start with map_head

};

void look_items_inRoom(Room *player_location, Item_list *itemList);

void look_transition_inRoom(Room *player_location);

void look_description_inRoom(Room *player_location);

void look_creatures_inRoom(Room *player_location, Creature_list *creatureList);

// Look around and see the all interaction options
void look_around(Room *player_location, Item_list *itemList, Creature_list *creatureList);

// direction -> 1(East), 2(West), 3(North), 4(Easth), 5(secret_passage)
void move(Player *myPlayer, int direction);

// Take the item you found in the room in your bag.
// If item there is in room
void pick_up(int itemId, Bag *myBag, Item_list *itemList, Player *myPlayer);

// When the item at hand changes, update stats
// If the player's hand is empty, it is not used !!!
void update_player_stats(Player *myPlayer, Item *old_item, Item *new_item);

// Pick up an item in the bag and hold it in your hand
void take_to_hand(int itemId, Player *myPlayer, Bag *myBag, Item_list *itemList, Input_list *myInputs);

void display_player_stats(Player *myPlayer);

void creature_fight(
    Player *myPlayer, 
    Creature_list *creatureList,
    Map *myMap,
    Bag *myBag,
    Input_list *myInputs);

// When the player dies
// Remove bag items
// Player born beginnig of the map
void player_death(Player *myPlayer, Bag *myBag, Map *myMap);

// When the creature dies
// The creature drops items in the room
// The creature removed from the room
void creature_death(int creatureId, Room *creature_location, Creature_list *creatureList);

#endif // PLAYER_H 