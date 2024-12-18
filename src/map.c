#include "../headers/map.h"


void add_room(Map *myMap){

    Room *new_room = (Room *)malloc(sizeof(Room));

    // if malloc fail
    if (new_room == NULL) {
        printf("Failed to allocate memory.\n");
        return;
    }

    if (myMap->number_of_room == 0)
    {
        myMap->map_head = new_room;
        myMap->map_tail = new_room;

        myMap->number_of_room ++;
        new_room->room_id = myMap->number_of_room;
    }
    else
    {
        myMap->map_tail->next_room_in_list = new_room;
        new_room->prev_room_in_list = myMap->map_tail;
        myMap->map_tail = new_room;

        myMap->number_of_room ++;
        new_room->room_id = myMap->number_of_room;
    }
    
}

void update_room_info(
    Map *myMap,
    int room_id,
    int room_items_id[3],
    int creature_id_inRoom,
    int right_id,
    int left_id,
    int front_id,
    int back_id,
    int bonusCon_id)
{

    Room *cursor = myMap->map_head; // use find the correct room
    Room *for_connec_cursor; // use connected to each other's room
    int check_update_room = -1; // Is there room to be updated?

    for (int i=0; i < myMap->number_of_room; i++)
    {
        if (room_id == cursor->room_id)
        {
            check_update_room = 1; // There's room to be updated. 

            // ~~~~~~~~~ for items id add ~~~~~~~~~
            for (int i = 0; i < 3; i++)
            {
                cursor->room_items_id[i] = room_items_id[i];
            }

            // ~~~~~~~~~ for creature id add ~~~~~~~~~
            cursor->creature_id_inRoom = creature_id_inRoom;

            // right,left,front,back,bonus connections all use same pattern same algorithm

            // ~~~~~~~~~ for right connection ~~~~~~~~~
            if(right_id != -1)
            {
                for_connec_cursor = myMap->map_head;
                int check_find = -1; // check for that room find or not

                for (int i = 0; i < myMap->number_of_room; i++)
                {
                    if(for_connec_cursor->room_id == right_id)
                    {
                        cursor->right_wall = for_connec_cursor;
                        check_find = 1;
                    }

                    for_connec_cursor = for_connec_cursor->next_room_in_list;
                }

                (check_find==-1) ? printf("id:%d NOT found !!! for id->%d room update\n",right_id,room_id) : 0;                
            }
            else
            {
                cursor->right_wall = NULL;
            }

            // ~~~~~~~~~ for left connection ~~~~~~~~~
            if(left_id != -1)
            {
                for_connec_cursor = myMap->map_head;
                int check_find = -1; // check for that room find or not

                for (int i = 0; i < myMap->number_of_room; i++)
                {
                    if(for_connec_cursor->room_id == left_id)
                    {
                        cursor->left_wall = for_connec_cursor;
                        check_find = 1;
                    }

                    for_connec_cursor = for_connec_cursor->next_room_in_list;
                }

                (check_find==-1) ? printf("id:%d NOT found !!! for id->%d room update\n",left_id,room_id) : 0;                
            }
            else
            {
                cursor->left_wall = NULL;
            }

            // ~~~~~~~~~ for front connection ~~~~~~~~~
            if(front_id != -1)
            {
                for_connec_cursor = myMap->map_head;
                int check_find = -1; // check for that room find or not

                for (int i = 0; i < myMap->number_of_room; i++)
                {
                    if(for_connec_cursor->room_id == front_id)
                    {
                        cursor->front_wall = for_connec_cursor;
                        check_find = 1;
                    }

                    for_connec_cursor = for_connec_cursor->next_room_in_list;
                }

                (check_find==-1) ? printf("id:%d NOT found !!! for id->%d room update\n",front_id,room_id) : 0;                
            }
            else
            {
                cursor->front_wall = NULL;
            }

            // ~~~~~~~~~ for back connection ~~~~~~~~~
            if(back_id != -1)
            {
                for_connec_cursor = myMap->map_head;
                int check_find = -1; // check for that room find or not

                for (int i = 0; i < myMap->number_of_room; i++)
                {
                    if(for_connec_cursor->room_id == back_id)
                    {
                        cursor->back_wall = for_connec_cursor;
                        check_find = 1;
                    }

                    for_connec_cursor = for_connec_cursor->next_room_in_list;
                }

                (check_find==-1) ? printf("id:%d NOT found !!! for id->%d room update\n",back_id,room_id) : 0;                
            }
            else
            {
                cursor->back_wall = NULL;
            }

            // ~~~~~~~~~ for bonus connection ~~~~~~~~~
            if(bonusCon_id != -1)
            {
                for_connec_cursor = myMap->map_head;
                int check_find = -1; // check for that room find or not

                for (int i = 0; i < myMap->number_of_room; i++)
                {
                    if(for_connec_cursor->room_id == bonusCon_id)
                    {
                        cursor->bonus_connection = for_connec_cursor;
                        check_find = 1;
                    }

                    for_connec_cursor = for_connec_cursor->next_room_in_list;
                }

                (check_find==-1) ? printf("id:%d NOT found !!! for id->%d room update\n",bonusCon_id,room_id) : 0;                
            }
            else
            {
                cursor->bonus_connection = NULL;
            }
            
        }

        cursor = cursor->next_room_in_list;        
    }
    
    (check_update_room == -1) ? printf("No room id=%d to be updated\n",room_id) : 0; 
}

int find_number_of_rooms()
{

    FILE *file = fopen(GAME_DATA_PATH "rooms.txt", "r");
    if (file == NULL) {
        printf("Can't find rooms.txt\n");
        return -1;
    }

    char line[100];  // Maximum expected number of characters with safety margin
    int count = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (line[0] == '*')
        {
            count++; // One more room add
        }
    }

    fclose(file);

    return count;
}

void load_room_infos(Map *myMap)
{

    FILE *file;
    char line[250]; // Maximum expected number of characters with safety margin

    file = fopen(GAME_DATA_PATH "rooms.txt", "r");

    if(file == NULL)
    {
        perror("Can't find rooms.txt");
        return;
    }

    while(fgets(line, sizeof(line), file)) // read all line in file
    {
        if(line[0] != '*') // line head must be * for meaning line
        {
            continue;
        }

        // Remove the last space and newline characters in the line
        line[strcspn(line, "\n")] = 0;
        line[strcspn(line, "\r")] = 0;

        char *token = strtok(line + 2, "/");
        int room_data[10];
        int counter = 0;
        while(token != NULL && counter < 10) // double safety, info number must 10 and token must NULL
        {
            room_data[counter] = atoi(token);
            counter++;
            token = strtok(NULL, "/");
        }

        int room_items_id[3] = {room_data[1],room_data[2],room_data[3]};

        update_room_info( // load infos to map
        myMap,
        room_data[0],
        room_items_id,
        room_data[4],
        room_data[5],
        room_data[6],
        room_data[7],
        room_data[8],
        room_data[9]);
    }

}

Room* find_room_map(int roomId, Map *myMap)
{

    Room *cursor = myMap->map_head;

    for (int i = 0; i < myMap->number_of_room; i++)
    {
        if(cursor->room_id == roomId)
        {
            return cursor; // room found
        }
        cursor = cursor->next_room_in_list;
    }
    
    return NULL;
}

void load_room_description(Map *myMap)
{

    FILE *file;
    char line[500]; // Maximum expected number of characters with safety margin

    file = fopen(GAME_DATA_PATH "room_descriptions.txt", "r");

    if (file == NULL) {
        printf("Can't find room_descriptions.txt\n");
        return;
    }

    Room *room_load = NULL;
    
    while (fgets(line, sizeof(line), file)) // read all line in file
    { 
        if (line[0] == '*')
        { 
            fgets(line, sizeof(line), file);
            int room_id = atoi(line);
            room_load = find_room_map(room_id, myMap);
            if(room_load == NULL){break;} // for safety

            while(fgets(line, sizeof(line), file))
            {
                if(line[0] == '~')
                {
                    break;
                }

                strcat(room_load->description, line);
            }
        } 
    }

    fclose(file);

}