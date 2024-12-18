#include "../headers/item_list.h"

Item *add_items_list(Item_list *itemList)
{

    Item *new_item = (Item *)malloc(sizeof(Item));

    if(itemList->number_of_item_list == 0)
    {
        itemList->item_list_head = new_item;
        itemList->item_list_tail = new_item;
        itemList->number_of_item_list++;
    }
    else
    {
        new_item->prev_item = itemList->item_list_tail;
        itemList->item_list_tail->next_item = new_item;
        itemList->item_list_tail = new_item;
        itemList->number_of_item_list++;
    }

    return new_item;
}

void load_item_infos(Item_list *itemList) // Add items from file "items.txt" to the list
{

    FILE *file;
    char line[57]; // Maximum expected number of characters with safety margin

    file = fopen(GAME_DATA_PATH "items.txt", "r");

    if(file == NULL)
    {
        perror("Can't find items.txt\n");
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
        char item_data[5][10];
        int counter = 0;
        while(token != NULL && counter < 5) // double safety, info number must 5 and token must NULL
        {
            strncpy(item_data[counter], token, 10);  // copy the string with strncpy
            item_data[counter][9] = '\0';  // make last charecter null for safety
            counter++;
            token = strtok(NULL, "/");
        }

        // yeni düğüm oluştur ve listeye ekle, load_item bu yeni düğümü gösteriyor
        Item *load_item = add_items_list(itemList); 

        for (int i = 0; i < 5; i++)
        {
            switch (i)
            {
                case 0:
                    load_item->item_id = atoi(item_data[i]); // gerekli strinler inr dönüşüp ekleniyor
                    break;
                case 1:
                    strcpy(load_item->item_name, item_data[i]); // copy string
                    break;
                case 2:
                    load_item->health_change = atoi(item_data[i]);
                    break;
                case 3:
                    load_item->damage_up = atoi(item_data[i]);
                    break;
                case 4:
                    load_item->shield_up = atoi(item_data[i]);
                    break;
            }
        }
        
    }

    fclose(file);
}

void display_item_list(Item_list *itemList)
{

    Item *cursor = itemList->item_list_head;

    if(itemList->number_of_item_list > 0)
    {
        for (int i = 0; i < itemList->number_of_item_list; i++)
        {
            printf("\nItem id : %d\n", cursor->item_id);
            printf("Item name : %s\n", cursor->item_name);
            printf("Item health_change : %d\n", cursor->health_change);
            printf("Item damege_up : %d\n", cursor->damage_up);
            printf("Item shield_up : %d\n", cursor->shield_up);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

            cursor = cursor->next_item;
        }
        
    }
    else
    {
        printf("NO item in item_list");
    }

}

Item* find_item_itemList(int itemId, Item_list *itemList)
{

    Item *cursor = itemList->item_list_head;

    for (int i = 0; i < itemList->number_of_item_list; i++)
    {
        if(cursor->item_id == itemId)
        {
            return cursor; // item found
        }
        cursor = cursor->next_item;
    }
    
    return NULL;
}