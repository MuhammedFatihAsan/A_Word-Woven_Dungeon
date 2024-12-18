#include "../headers/player.h"

void look_items_inRoom(Room *player_location, Item_list *itemList)
{

    printf("\n$$Items in the room :\n");

    for (int i = 0; i < 3; i++)
    {
        Item *item_in_room = find_item_itemList(player_location->room_items_id[i], itemList);

        if(item_in_room != NULL)
        {
            printf("-->Id:%d %s (Damage:%d Shield:%d Heal:%d)\n",
                item_in_room->item_id,
                item_in_room->item_name,
                item_in_room->damage_up,
                item_in_room->shield_up,
                item_in_room->health_change);
        }
    }

}

void look_transition_inRoom(Room *player_location)
{

    printf("\n||Transition information :\n");

    printf("-->There is a transition on the ");
    if(player_location->right_wall != NULL)
    {
        printf("'East', ");
    }
    if(player_location->left_wall != NULL)
    {
        printf("'West', ");
    }
    if(player_location->front_wall != NULL)
    {
        printf("'North', ");
    }
    if(player_location->back_wall != NULL)
    {
        printf("'South', ");
    }
    printf("side...\n");
    if(player_location->bonus_connection != NULL)
    {
        printf("-->What the hell is that? There seems to be a 'secret_passage' in the floor !\n");
    }

}

void look_description_inRoom(Room *player_location)
{

    printf("***%s", player_location->description);

}

void look_creatures_inRoom(Room *player_location, Creature_list *creatureList)
{

    Creature *creature_in_room = find_creature_creatureList(player_location->creature_id_inRoom, creatureList);

    if(creature_in_room != NULL)
    {
        printf("\nCREATURE !!!\n");
        printf("~~~(o_o)~~~ | HP : %d | Attack : %d\n",
            creature_in_room->creature_health,
            creature_in_room->creature_damage);
    }

}

void look_around(Room *player_location, Item_list *itemList, Creature_list *creatureList)
{

    look_description_inRoom(player_location);
    look_items_inRoom(player_location, itemList);
    look_transition_inRoom(player_location);
    look_creatures_inRoom(player_location, creatureList);

}

void move(Player *myPlayer, int direction) // direction -> 1(East), 2(West), 3(North), 4(Easth), 5(secret_passage)
{

    switch (direction)
            {
            case 1:
                if(myPlayer->player_location->right_wall != NULL)
                {
                    myPlayer->player_location = myPlayer->player_location->right_wall;
                    printf("\n=> I went through the east gate. Now what?\n");
                }
                else
                {
                    printf("\n=> There's no passage this way!! Are you kidding me?!\n");
                }
                break;
            
            case 2:
                if(myPlayer->player_location->left_wall != NULL)
                {
                    myPlayer->player_location = myPlayer->player_location->left_wall;
                    printf("\n=> I went through the west gate. Now what?\n");
                }
                else
                {
                    printf("\n=> There's no passage this way!! Are you kidding me?!\n");
                }
                break;
            
            case 3:
                if(myPlayer->player_location->front_wall != NULL)
                {
                    myPlayer->player_location = myPlayer->player_location->front_wall;
                    printf("\n=> I went through the north gate. Now what?\n");
                }
                else
                {
                    printf("\n=> There's no passage this way!! Are you kidding me?!\n");
                }
                break;
            
            case 4:
                if(myPlayer->player_location->back_wall != NULL)
                {
                    myPlayer->player_location = myPlayer->player_location->back_wall;
                    printf("\n=> I went through the south gate. Now what?\n");
                }
                else
                {
                    printf("\n=> There's no passage this way!! Are you kidding me?!\n");
                }
                break;

            case 5:
                if(myPlayer->player_location->bonus_connection != NULL)
                {
                    myPlayer->player_location = myPlayer->player_location->bonus_connection;
                    printf("\n=> I went through the east gate. Now what?\n");
                }
                else
                {
                    printf("\n=> HA HA HA HA Secret passage? Where is it?!!\n");
                }
                break;
            
            default:
                printf("\n=> I don't know what you're talking about! Are you sure you're okay?\n");
                break;
            }

}

void pick_up(int itemId, Bag *myBag, Item_list *itemList, Player *myPlayer)
{

    Item *item_to_add = find_item_itemList(itemId, itemList); //find and assign item in item list
    int check_add = -1;

    if(item_to_add != NULL)
    {
        
        for (int i = 0; i < 3; i++)
        {
            if(myPlayer->player_location->room_items_id[i] == itemId)//Is the item in the room
            {
                check_add = 1;

                 if(itemId == 1)
                {
                    myPlayer->key_count++;
                    myPlayer->key_check[0] = 1;
                    Item *item_to_add = find_item_itemList(itemId, itemList);
                    printf("WAOOV We finded a key : %s", item_to_add->item_name);
                    return;
                }
                if(itemId == 2)
                {
                    myPlayer->key_count++;
                    myPlayer->key_check[1] = 1;
                    Item *item_to_add = find_item_itemList(itemId, itemList);
                    printf("WAOOV We finded a key : %s", item_to_add->item_name);
                    return;
                }
                if(itemId == 3)
                {
                    myPlayer->key_count++;
                    myPlayer->key_check[2] = 1;
                    Item *item_to_add = find_item_itemList(itemId, itemList);
                    printf("WAOOV We finded a key : %s", item_to_add->item_name);
                    return;
                }

                add_item_bag(
                    myBag,
                    item_to_add->item_id,
                    item_to_add->item_name,
                    item_to_add->health_change,
                    item_to_add->damage_up,
                    item_to_add->shield_up);
            }
        }
        
    }
    if(check_add == -1)
    {
        printf("\n=> Dude, I can't find an id:%d item in this room.", itemId);
    }

}

void update_player_stats(Player *myPlayer, Item *old_item, Item *new_item)
{

    if(old_item == NULL && new_item != NULL)
    {
        myPlayer->player_hp += new_item->health_change;
        myPlayer->player_atack_power += new_item->damage_up;
        myPlayer->player_shield_power += new_item->shield_up;

        

        printf("\n=> I took the %s from Inventory in my hand.\n",
            new_item->item_name);
    }
    else if(old_item != NULL && new_item != NULL)
    {
        myPlayer->player_hp -= old_item->health_change;
        myPlayer->player_atack_power -= old_item->damage_up;
        myPlayer->player_shield_power -= old_item->shield_up;

        myPlayer->player_hp += new_item->health_change;
        myPlayer->player_atack_power += new_item->damage_up;
        myPlayer->player_shield_power += new_item->shield_up;

        printf("\n=> I took the %s from Inventory in my hand.\n",
            new_item->item_name);
    }
    else
    {
        printf("# There is a mistake, update_player_stats()");
    }

}


void take_to_hand(int itemId, Player *myPlayer, Bag *myBag, Item_list *itemList, Input_list *myInputs)
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
            if (scanf("%d", &c4) != 1) {while (getchar() != '\n');}// make sure int is entered
            add_input(c4, myInputs);
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

void display_player_stats(Player *myPlayer)
{

    printf("]\n]Dilemma --> HP:%d Atack_P:%d Shield_P:%d\n",
        myPlayer->player_hp,myPlayer->player_atack_power,myPlayer->player_shield_power);

    printf("]Key Count : %d\n",myPlayer->key_count);
    printf("]Lost key count : %d\n",(3-myPlayer->key_count));

}

void creature_fight(
    Player *myPlayer, 
    Creature_list *creatureList,
    Map *myMap,
    Bag *myBag,
    Input_list *myInputs)
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
            if (scanf("%d", &c5) != 1) {while (getchar() != '\n');}// make sure int is entered
            add_input(c5, myInputs);
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

void player_death(Player *myPlayer, Bag *myBag, Map *myMap)
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
    
    myPlayer->player_location = myMap->map_head;
    myPlayer->player_hp = 100;
    // The life values of the items in your hand must be added again
    myPlayer->player_hp += myPlayer->player_right_hand->health_change;
    myPlayer->player_hp += myPlayer->player_left_hand->health_change;

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("# All the items in your bag are gone because you died.\n");
    printf("# You only have the items you're holding.\n");
    printf("# You were born at the starting point of the map.\n");
    printf("# You have nothing but what you have.\n");
    printf("# I pity you.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

}

void creature_death(int creatureId, Room *creature_location, Creature_list *creatureList)
{
    Creature *died_creature = find_creature_creatureList(creatureId, creatureList);

    int check = -1;

    for (int i = 0; i < 3; i++)
    {
        if(creature_location->room_items_id[i] == -1)
        {
            creature_location->room_items_id[i] = died_creature->item_id; // The creature drops items in the room
            check = 1;
            break;
        }
    }

    if(check == -1)
    {
        creature_location->room_items_id[2] = died_creature->item_id;
    }
    
    creature_location->creature_id_inRoom = -1; // The creature removed from the room

    printf("\n//////////////////////////////////////////////////////\n");
    printf("# The creature is dead.\n");
    printf("# He will never be born again.\n");
    if(died_creature->item_id > 0)
    {
        printf("# Creature dropped the item in room\n");
        printf("# I think you should check it out.\n");
    }
    printf("//////////////////////////////////////////////////////\n");

}