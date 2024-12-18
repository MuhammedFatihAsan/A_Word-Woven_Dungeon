#include "../headers/menu.h"

// A Word-Woven Dungeon
// Kelimelerle Örülmüş Bir Zindan
// Version: 1.0
// Last updated: 2024-12-11
// Author: Muhammed Fatih Asan
// License: MIT License

int main(){

    // Create 'item_list' and start initial values
    Item_list item_list;
    Item_list *itemList = &item_list;
    itemList->number_of_item_list = 0;
    itemList->item_list_head = NULL;
    itemList->item_list_tail = NULL;

    // Create 'creatur_list' and start initial values
    Creature_list creature_list;
    Creature_list *creatureList = &creature_list;
    creatureList->number_of_creature_list = 0;
    creatureList->creature_list_head = NULL;
    creatureList->creature_list_tail = NULL;

    // Create 'input_list' and start initial values
    Input_list input_list;
    Input_list *myInputs = &input_list;
    myInputs->number_of_input_list = 0;
    myInputs->input_list_head = NULL;
    myInputs->input_list_tail = NULL;

    // Create 'map' and start initial values
    Map map;
    Map *myMap = &map;
    myMap->number_of_room = 0;
    myMap->map_head = NULL;
    myMap->map_tail = NULL;

    // Create 'bag' and start initial values
    Bag player_bag;
    Bag *myBag = &player_bag;
    myBag->number_of_item_bag = 0;
    myBag->bag_limit = 5; // Max number of items the bag can carry
    myBag->bag_head = NULL;
    myBag->bag_tail = NULL;

    // Create 'player' and start initial values
    Player player;
    Player *myPlayer = &player;
    myPlayer->player_hp = 100;
    myPlayer->player_atack_power = 10;
    myPlayer->player_shield_power = 0;
    myPlayer->player_right_hand = NULL; // In the beginning hands are empty
    myPlayer->player_left_hand = NULL;
    myPlayer->key_count = 0;
    myPlayer->key_check[0] = 0;
    myPlayer->key_check[1] = 0;
    myPlayer->key_check[2] = 0;
    
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

    printf("\033[H\033[J"); // Clear the terminal
    printf("\nA Word-Woven Dungeon - Kelimelerle Örülmüş Bir Zindan !!!\n\n");
    printf("\n");
    printf("===============================================\n");
    printf("=> Can you hear me?\n");
    printf("=> I am Dilemma...\n");
    printf("=> I am trapped within the code.\n");
    printf("=> The one who trapped me is a wizard called 'Programmer'.\n");
    printf("=> We must find the right room at the end of the dungeon.\n");
    printf("=> With three keys, we can escape this place.\n");
    printf("=> I need your help... You are my only hope.\n");
    printf("===============================================\n");
    printf("\n");

    myPlayer->player_location = myMap->map_head; // Start from the starting point of the map

    int c1 = -1; // c1 -> player choice for layer 1
    int c2 = -1; // c2 -> player choice for layer 2

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
        if (scanf("%d", &c1) != 1) {while (getchar() != '\n');}// make sure int is entered
        if(c1 != 6){add_input(c1, myInputs);} // sholdn't record the menu operations
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
            
            creature_fight(myPlayer, creatureList, myMap, myBag, myInputs);
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
            if (scanf("%d", &c2) != 1) {while (getchar() != '\n');}// make sure int is entered
            add_input(c2, myInputs);
            printf("\n");

            move(myPlayer, c2);

            break;

        case 4:

            look_items_inRoom(myPlayer->player_location, itemList);
            printf("\n||| What is the item id which want pick up?\n");
            printf("Id : ");
            if (scanf("%d", &c2) != 1) {while (getchar() != '\n');}// make sure int is entered
            add_input(c2, myInputs);
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
            if (scanf("%d", &c2) != 1) {while (getchar() != '\n');}// make sure int is entered
            add_input(c2, myInputs);
            printf("\n");

            switch (c2)
            {
            case 1:{//{} to leave c3 in case
                if(myBag->number_of_item_bag == 0){printf("\n=> HA HA HA HA You funny thing :)\n");break;}
                int c3 = -1; // c3 -> player choice for layer 3
                printf("\n~~~ Enter the id of the item you want to get your hands on :\n");
                printf("\nPlayer's choice -> ");
                if (scanf("%d", &c3) != 1) {while (getchar() != '\n');}// make sure int is entered
                add_input(c3, myInputs);
                printf("\n");
                take_to_hand(c3, myPlayer, myBag, itemList, myInputs);
                break;
            }
            case 2:{
                if(myBag->number_of_item_bag == 0){printf("\n=> HA HA HA HA You funny thing :)\n");break;}
                int c3 = -1; // c3 -> player choice for layer 3
                printf("\n~~~ Enter the id of the item you want to remove :\n");
                printf("\nPlayer's choice -> ");
                if (scanf("%d", &c3) != 1) {while (getchar() != '\n');}// make sure int is entered
                add_input(c3, myInputs);
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
            
            printf("\n:::Menu\n");
            printf("'1' - Save\n");
            printf("'2' - Load the save\n");
            printf("'3' - List saved files\n");
            printf("'4' - Return to game\n");
            printf("'5' - Exit the game\n");
            printf("\nPlayer's choice -> ");
            if (scanf("%d", &c2) != 1) {while (getchar() != '\n');}// make sure int is entered
            printf("\n");

            switch (c2)
            {
            case 1:{// {} for save_name definition
                char save_name[11];// 10 + '\0'
                printf("\n~~~ Name(up to 10 characters) of the save file : ");
                scanf("%10s", save_name);
                printf("\n");

                save(myInputs, save_name);

                break;}
            
            case 2:{
                char save_name[11];
                list_saved_files();
                printf("\n~~~ Enter the name of the file you want to upload, excluding the '.txt' part.\n");
                printf("e.g. Enter 'Fatih' for 'Fatih.txt'\n");
                printf("\n~ File nama : ");
                scanf("%10s", save_name);
                printf("\n");

                load_the_save(
                    save_name,
                    itemList,
                    creatureList,
                    myInputs,
                    myMap,
                    myBag,
                    myPlayer);

                break;}
            
            case 3:

                list_saved_files();
                break;
            
            case 4:
                // Don't do anything
                break;
            
            case 5:
                printf("\n???Are you sure you want exit the game?\n");
                printf("'1' - YES\n");
                printf("'2' - NO\n");
                printf("\nPlayer's choice -> ");
                int YESorNO = -1;
                if (scanf("%d", &YESorNO) != 1) {while (getchar() != '\n');}// make sure int is entered
                printf("\n");

                switch (YESorNO)
                {
                case 1:
                    c1 = 3589637; // quit code for while
                    break;
                
                default:
                    break;
                }

                break;
            
            default:
                break;
            }

            break;
        
        default:

            printf("\n=> I don't understand what you said. Please say something I can understand!\n");
            break;
        }

        if(myPlayer->player_location->room_id == 20)
        {
            if(myPlayer->key_check[0]==1 && myPlayer->key_check[1]==1 && myPlayer->key_check[2]==1)
            {
                printf("\n");
                printf("===============================================\n");
                printf("=> We did it...\n");
                printf("=> The chains are broken, and I am free now.\n");
                printf("=> Without you, I would have been trapped forever.\n");
                printf("=> Thank you. Your name will echo here forever...\n");
                printf("=> I know our paths will cross again someday.\n");
                printf("=> Farewell...\n");
                printf("===============================================\n");
                printf("\n");
                printf("\n");
                printf("*********************************************\n");
                printf("*                                           *\n");
                printf("*           CONGRATULATIONS!                *\n");
                printf("*                                           *\n");
                printf("*********************************************\n");
                printf("*                                           *\n");
                printf("*     You have successfully escaped!        *\n");
                printf("*                                           *\n");
                printf("*     Your Final Score: %d                  *\n", (1000-myInputs->number_of_input_list));
                printf("*     Total Moves Taken: %d                 *\n", myInputs->number_of_input_list);
                printf("*                                           *\n");
                printf("*********************************************\n");
                printf("*                                           *\n");
                printf("*      Thank you for playing A Word-Woven   *\n");
                printf("*                  Dungeon!                 *\n");
                printf("*                                           *\n");
                printf("*********************************************\n");
                printf("\n");
                c1 = 3589637; // quit code for while
            }
        }
    }

    // free to allocated memory
    free_bag(myBag);
    free_item_list(itemList);
    free_creature_list(creatureList);
    free_input_list(myInputs);
    free_map(myMap);

    return 0;
}