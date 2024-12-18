#ifndef MAP_H
#define MAP_H

#include "./room.h"

typedef struct Map Map;

struct Map{

    int number_of_room; // start with 0
    Room *map_head; // start with NULL
    Room *map_tail; // start with NULL

};

void add_room(Map *myMap);

void update_room_info(    // update all room data
    Map *myMap,
    int room_id,
    int room_items_id[3],
    int creature_id_inRoom,
    int right_id,
    int left_id,
    int front_id,
    int back_id,
    int bonusCon_id);

// Find the number of rooms in the file 'rooms.txt'
// Return -1 means is fail
int find_number_of_rooms();

// load all room infos from 'rooms.txt' except description
void load_room_infos(Map *myMap);

// if can't find return NULL
Room* find_room_map(int roomId, Map *myMap);

// load room description infos from 'room_descriptions.txt'
void load_room_description(Map *myMap);

#endif // MAP_H