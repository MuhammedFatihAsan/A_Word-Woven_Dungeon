#ifndef ROOM_H
#define ROOM_H

#include "./item_list.h"
#include "./creature_list.h"

typedef struct Room Room;

struct Room{
 
    int room_id;

    char description[1000];
    int room_items_id[3];
    int creature_id_inRoom;

    /* Variables are named right, left, etc. according to the map.
    East, west, north, south will be used in the interface to avoid
    player confusion */
    Room *right_wall; // east
    Room *left_wall; // west
    Room *front_wall; // north
    Room *back_wall; // south

    Room *bonus_connection; // for extra connections(stairs, secret passages etc.)

    Room *next_room_in_list; // base room data uses linked list
    Room *prev_room_in_list;

};

#endif // ROOM_H