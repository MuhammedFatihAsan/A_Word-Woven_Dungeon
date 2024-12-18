#include "../headers/menu.h"

void save(Input_list *myInputs, char save_name[11])
{

    FILE *file;
    
    char file_path[250]; // safety space for path
    sprintf(file_path, "%s%s%s.txt", GAME_DATA_PATH, "save_files/", save_name);

    file = fopen(file_path, "w");

    if (file == NULL) {
        printf("# Failed to create file! Check the running file permissions or\n");
        printf("file structure may also be path error !!");
        return;
    }

    Input *cursor = myInputs->input_list_head;

    for (int i = 0; i < myInputs->number_of_input_list; i++)
    {
        fprintf(file, "%d\n", cursor->input);
        cursor = cursor->nxt_input;
        if(cursor == NULL){break;} // for safety
    }
    

    fclose(file);

    printf("\n# Your progress is recorded.\n# Path to your save file :\n\n");
    printf("%s",file_path);
    printf("\n");

}

void list_saved_files()
{

    struct dirent *entry; // Structure for directory entry
    DIR *dp; // Directory pointer

    char file_path[250]; // safety space for path
    sprintf(file_path, "%s%s", GAME_DATA_PATH, "save_files");

    char *folder_path = file_path;

    // Open the directory
    dp = opendir(folder_path);
    if (dp == NULL) {
        printf("\n# Failed to open the directory for 'list_saved_files()'\n");
        return;
    }

    printf("\n# Path of the accessed save files :\n");
    printf("'.%s'\n", folder_path);

    printf("\n# All saved save files(.txt) :\n");

    int counter = 1;
    while ((entry = readdir(dp)) != NULL) { // Read the contents of the directory
        // Check if the file name ends with .txt
        if (strstr(entry->d_name, ".txt") != NULL) {
            printf("%d) %s\n", counter, entry->d_name);
            counter++;
        }
    }

    // Close the directory
    closedir(dp);

}

void upload_progress(
    Input_list *myInputs,
    Item_list *itemList,
    Creature_list *creatureList,
    Map *myMap,
    Bag *myBag,
    Player *myPlayer)
{

    int c1 = -1; // c1 -> player choice for layer 1
    int c2 = -1; // c2 -> player choice for layer 2

    Input *input_cursor = myInputs->input_list_head;

    while(c1 != 3589637)// Ending code '3589637', 7 digits for security
    {   
        c1 = -1; //for invalid entries to be kept as -1
        c2 = -1; //important for save and load architectures

        printf("\n\n-------------------------------------------------");
        printf("\n]Number of actions:%d\n",myInputs->number_of_input_list);
        printf("]Score:%d\n",(1000-myInputs->number_of_input_list));
        display_player_stats(myPlayer);
        printf("\n>>>>>Interactions :\n");
        printf("'1' -> Look around\n");
        printf("'2' -> Attack\n");
        printf("'3' -> Move\n");
        printf("'4' -> Pick up the item\n");
        printf("'5' -> Open Inventory\n");
        printf("'6' -> Open Menu\n");
        printf("\nPlayer's choice -> ");
        //
        input_cursor = input_cursor->nxt_input;
        c1 = input_cursor->input;
        //
        printf("\033[H\033[J"); // Clear the terminal
        printf("\n");

        switch (c1)
        {
        case 1:

            if(myPlayer->player_location != NULL)
            {
                look_around(myPlayer->player_location, itemList, creatureList);
            }
            else
            {
                printf("\n# Player_location is showing an address it shouldn't !!!\n");
            }

            break;
        
        case 2:
            //
            input_cursor = input_cursor->nxt_input;
            creature_fight_load_version(myPlayer, creatureList, myMap, myBag, input_cursor->input);
            //
            break;
        
        case 3:
            
            look_transition_inRoom(myPlayer->player_location);
            printf("\n|||Choose direction\n");
            printf("'1' - East\n");
            printf("'2' - West\n");
            printf("'3' - North\n");
            printf("'4' - South\n");
            printf("'5' - Try secret pass\n");
            printf("\nDirection choice -> ");
            //
            input_cursor = input_cursor->nxt_input;
            c2 = input_cursor->input;
            //
            printf("\n");

            move(myPlayer, c2);

            break;

        case 4:

            look_items_inRoom(myPlayer->player_location, itemList);
            printf("\n||| What is the item id which want pick up?\n");
            printf("Id : ");
            //
            input_cursor = input_cursor->nxt_input;
            c2 = input_cursor->input;
            //
            printf("\n");
            pick_up(c2, myBag, itemList, myPlayer);
            break;

        case 5:
            
            display_bag(myBag);
            int c2 = -1; // c2 -> player choice for layer 2
            printf("\n|||What do you want to do in inventory?\n");
            printf("'1' -> Take an item in your hand!\n");
            printf("'2' -> Remove items from Inventory.(The item you remove is completely gone!!!)\n");
            printf("'3' -> I just look, don't change anythin.\n");
            printf("\nPlayer's choice -> ");
            //
            input_cursor = input_cursor->nxt_input;
            c2 = input_cursor->input;
            //
            printf("\n");

            switch (c2)
            {
            case 1:{//{} to leave c3 in case
                if(myBag->number_of_item_bag == 0){printf("\n=> HA HA HA HA You funny thing :)\n");break;}
                int c3 = -1; // c3 -> player choice for layer 3
                printf("\n~~~ Enter the id of the item you want to get your hands on :\n");
                printf("\nPlayer's choice -> ");
                //
                input_cursor = input_cursor->nxt_input;
                c3 = input_cursor->input;
                //
                printf("\n");
                //take_to_hand -> start
                input_cursor = input_cursor->nxt_input;
                take_to_hand_load_version(c3, myPlayer, myBag, itemList, input_cursor->input);
                //take_to_hand -> finish
                break;
            }
            case 2:{
                if(myBag->number_of_item_bag == 0){printf("\n=> HA HA HA HA You funny thing :)\n");break;}
                int c3 = -1; // c3 -> player choice for layer 3
                printf("\n~~~ Enter the id of the item you want to remove :\n");
                printf("\nPlayer's choice -> ");
                //
                input_cursor = input_cursor->nxt_input;
                c3 = input_cursor->input;
                //
                printf("\n");
                remove_item_bag(myBag, c3);
                break;
            }
            case 3:
                // Don't do anything
                break;
            
            default:
                printf("\n=> I think you slipped your tongue :D\n");
                break;
            }
            
            break;

        case 6:
            
            //don't do anything
            //we don't need menu when load to save
            break;
        }

    }

}

void load_the_save(
    char file_name[11],
    Item_list *itemList,
    Creature_list *creatureList,
    Input_list *myInputs,
    Map *myMap,
    Bag *myBag,
    Player *myPlayer)
{

    FILE *file;
    
    char file_path[250]; // safety space for path
    sprintf(file_path, "%s%s%s.txt", GAME_DATA_PATH, "save_files/", file_name);

    file = fopen(file_path, "r");

    if(file == NULL)
    {
        printf("\n# Can't find %s.txt\n\n", file_name);
        return;
    }

    char line[100]; // Maximum expected number of characters with safety margin

    free_input_list(myInputs); // reset input_list
    add_input(-1, myInputs); // first input must be unneceary for load progress

    while(fgets(line, sizeof(line), file)) // read all line in file
    {
        // Remove the last space and newline characters in the line
        line[strcspn(line, "\n")] = 0;
        line[strcspn(line, "\r")] = 0;

        add_input(atoi(line), myInputs); // empty input list
    }

    // all data reset for load save
    // ~~~~~
    free_bag(myBag);
    free_item_list(itemList);
    free_creature_list(creatureList);
    free_map(myMap);

    /* The required number of rooms is created before uploading the room information.
    Because in order to connect the rooms to each other, all of them must be created first. */
    for (int i = 0; i < find_number_of_rooms(); i++) // read it 'rooms.txt'
    {
        add_room(myMap);
    }

    // Load txt file infos -> 'items.txt' 'creatures.txt' 'rooms.txt' 'room_descriptions.txt'
    load_item_infos(itemList);
    load_creature_infos(creatureList);
    load_room_infos(myMap); // Must be loaded after item-infos & creature-infos
    load_room_description(myMap); // Should be load after room-infos

    myPlayer->player_location = myMap->map_head;
    myPlayer->player_hp = 100;
    myPlayer->player_atack_power = 10;
    myPlayer->player_shield_power = 0;
    myPlayer->player_left_hand = NULL;
    myPlayer->player_right_hand = NULL;
    myPlayer->key_check[0] = -1;
    myPlayer->key_check[1] = -1;
    myPlayer->key_check[2] = -1;
    myPlayer->key_count = 0;

    // ~~~~~

    add_input(3589637, myInputs);// for finish the load (last input)

    upload_progress(
        myInputs,
        itemList,
        creatureList,
        myMap,
        myBag,
        myPlayer);

    // Remove the exit code from the entry list after the registration upload is finished
    myInputs->input_list_tail = myInputs->input_list_tail->prv_input;
    myInputs->input_list_tail->nxt_input = NULL;
    // Remove the startup input required for file load
    myInputs->input_list_head = myInputs->input_list_head->nxt_input;
    myInputs->input_list_head->prv_input = NULL;

    printf("\n# Your progress has been read and loaded from the file named '%s.txt'\n",file_name);
    printf("# You can continue your adventure, good luck!!\n\n");

    fclose(file);

}

void free_item_list(Item_list *itemList)
{
    if (itemList == NULL || itemList->item_list_tail == NULL) {
        return;
    }

    Item *cursor = itemList->item_list_tail;

    while (cursor != NULL) {
        Item *temporary = cursor->prev_item;
        free(cursor);
        cursor = temporary;
    }

    itemList->item_list_head = NULL;
    itemList->item_list_tail = NULL;
    itemList->number_of_item_list = 0;
}

void free_input_list(Input_list *myInputs)
{
    if (myInputs == NULL || myInputs->input_list_tail == NULL) {
        return;
    }

    Input *cursor = myInputs->input_list_tail;

    while (cursor != NULL) {
        Input *temporary = cursor->prv_input;
        free(cursor);
        cursor = temporary;
    }

    myInputs->input_list_head = NULL;
    myInputs->input_list_tail = NULL;
    myInputs->number_of_input_list = 0;
}

void free_bag(Bag *myBag)
{
    if (myBag == NULL || myBag->bag_tail == NULL) {
        return;
    }

    Item *cursor = myBag->bag_tail;

    while (cursor != NULL) {
        Item *temporary = cursor->prev_item;
        free(cursor);
        cursor = temporary;
    }

    myBag->bag_head = NULL;
    myBag->bag_tail = NULL;
    myBag->number_of_item_bag = 0;
    myBag->bag_limit = 5;
}

void free_creature_list(Creature_list *creatureList)
{
    if (creatureList == NULL || creatureList->creature_list_tail == NULL) {
        return;
    }

    Creature *cursor = creatureList->creature_list_tail;

    while (cursor != NULL) {
        Creature *temporary = cursor->prev_creature;
        free(cursor);
        cursor = temporary;
    }

    creatureList->creature_list_head = NULL;
    creatureList->creature_list_tail = NULL;
    creatureList->number_of_creature_list = 0;
}

void free_map(Map *myMap)
{
    if (myMap == NULL || myMap->map_tail == NULL) {
        return;
    }

    Room *cursor = myMap->map_tail;

    while (cursor != NULL) {
        Room *temporary = cursor->prev_room_in_list;
        free(cursor);
        cursor = temporary;
    }

    myMap->map_head = NULL;
    myMap->map_tail = NULL;
    myMap->number_of_room = 0;
}

void take_to_hand_load_version(
    int itemId,
    Player *myPlayer,
    Bag *myBag,
    Item_list *itemList,
    int cursor_input)
{

    Item *item_to_take = find_item_bag(itemId, myBag); //find and assign item in bag

    if(item_to_take != NULL)
    {
        if(myPlayer->player_right_hand == NULL)
        {
            update_player_stats(myPlayer, myPlayer->player_right_hand, item_to_take);
            // !!! It must show in the item list because the item in the bag will be deleted soon. !!!
            myPlayer->player_right_hand = find_item_itemList(item_to_take->item_id, itemList);
            remove_item_bag(myBag, item_to_take->item_id);
        }
        else if(myPlayer->player_left_hand == NULL)
        {
            update_player_stats(myPlayer, myPlayer->player_left_hand, item_to_take);
            // !!! It must show in the item list because the item in the bag will be deleted soon. !!!
            myPlayer->player_left_hand = find_item_itemList(item_to_take->item_id, itemList);
            remove_item_bag(myBag, item_to_take->item_id);
        }
        else
        {
            int c4 = -1; // c4 -> player choice for layer 3
            printf("\n=> Dude, my hands are full, how am I supposed to pick up?!\n");
            printf("Do you want to exchange one of the things you're holding in your hand?\n");
            printf("'1' -> Change with %s in right hand\n",myPlayer->player_right_hand->item_name);
            printf("'2' -> Change with %s in left hand\n",myPlayer->player_left_hand->item_name);
            printf("'3' -> I give up, don't change anythin\n");
            printf("\nPlayer's choice -> ");
            //
            c4 = cursor_input;
            //
            printf("\n");

            Item *temporary = NULL; // temporary item for exchange

            switch (c4)
            {
            case 1:
                // exchange for the item in the right hand
                update_player_stats(myPlayer, myPlayer->player_right_hand, item_to_take);
                temporary = myPlayer->player_right_hand;
                // !!! It must show in the item list because the item in the bag will be deleted soon. !!!
                myPlayer->player_right_hand = find_item_itemList(item_to_take->item_id, itemList);
                remove_item_bag(myBag, item_to_take->item_id);
                add_item_bag(
                    myBag,
                    temporary->item_id,
                    temporary->item_name,
                    temporary->health_change,
                    temporary->damage_up,
                    temporary->shield_up);

                break;
            
            case 2:
                // exchange for the item in the left hand
                update_player_stats(myPlayer, myPlayer->player_left_hand, item_to_take);
                temporary = myPlayer->player_left_hand;
                // !!! It must show in the item list because the item in the bag will be deleted soon. !!!
                myPlayer->player_left_hand = find_item_itemList(item_to_take->item_id, itemList);
                remove_item_bag(myBag, item_to_take->item_id);
                add_item_bag(
                    myBag,
                    temporary->item_id,
                    temporary->item_name,
                    temporary->health_change,
                    temporary->damage_up,
                    temporary->shield_up);

                break;
            
            case 3:
                // Don't do anything
                break;
            
            default:
                break;
            }
        }
    }
    else
    {
        printf("\n=> Id:%d I couldn't be found to it. Are you sure it exists?\n",itemId);
    }

}

void creature_fight_load_version(
    Player *myPlayer, 
    Creature_list *creatureList,
    Map *myMap,
    Bag *myBag,
    int cursor_input)
{

    Creature *creature_fight = find_creature_creatureList(myPlayer->player_location->creature_id_inRoom, creatureList);

    if(creature_fight != NULL)
    {
        while (1)
        {   
            printf("\033[H\033[J"); // Clear the terminal
            look_creatures_inRoom(myPlayer->player_location, creatureList);
            int c5 = -1; // c5 -> player choice for layer 3
            printf("\n=> Fight, huh. Okay, let's go !!!!\n");
            printf("#Every time you hit him, he hits you.\n\n");
            printf("'1' -> Attack!\n");
            printf("'2' -> Stop fighting.\n");
            printf("\nPlayer's choice -> ");
            //
            c5 = cursor_input;
            //
            printf("\n");

            if(c5 == 1)
            {
                creature_fight->creature_health -= myPlayer->player_atack_power;

                if(creature_fight->creature_health <= 0)
                {
                    creature_death(creature_fight->creature_id, myPlayer->player_location, creatureList);
                    break;
                }

                int overflow_damage = creature_fight->creature_damage - myPlayer->player_shield_power;

                if(overflow_damage >0)
                {
                    myPlayer->player_hp -= overflow_damage;
                }

                if(myPlayer->player_hp <= 0)
                {
                    player_death(myPlayer, myBag, myMap);
                    break;
                }
            }
            else if(c5 == 2)
            {
                printf("\n=> Tactical retreat, NO white flag !!!\n");
                break;
            }
        }  
    }
    else
    {
        printf("\n=> You're delusional! No creature!!\n");
    }

}