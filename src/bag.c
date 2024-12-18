#include "../headers/bag.h"

void add_item_bag(
    Bag *myBag,
    int item_id,
    char item_name[10],
    int health_change,
    int damage_up,
    int shield_up)
{

    if(myBag->bag_limit >= myBag->number_of_item_bag) // The limit for adding items should be sufficient
    {
        Item *new_item = (Item *)malloc(sizeof(Item));

        // if malloc fail
        if(new_item == NULL){
            printf("#Failed to allocate memory.\n");
            return;
        }

        if(myBag->number_of_item_bag == 0)
        {
            myBag->bag_head = new_item;
            myBag->bag_tail = new_item;

            myBag->number_of_item_bag ++;
        }
        else if(myBag->number_of_item_bag > 0)
        {
            myBag->bag_tail->next_item = new_item;
            new_item->prev_item = myBag->bag_tail;
            myBag->bag_tail = new_item;

            myBag->number_of_item_bag ++;
        }
        else
        {
            printf("#Item count is negative in bag. Must be a mistake !!!\n");
        }

        new_item->item_id = item_id;
        strcpy(new_item->item_name, item_name); // copy string
        new_item->health_change = health_change;
        new_item->damage_up = damage_up;
        new_item->shield_up = shield_up;
        printf("\n=> All right, I put the %s in the bag!\n", item_name);
    }
    else
    {
        printf("\n=> Dude, I don't have any space in my bag!\n");
        printf("=> Should we throw something out of the bag?\n");
    }

}

void remove_item_bag(Bag *myBag, int item_id)
{

    Item *item_cursor = myBag->bag_head;
    int check_find = -1; // is thre that id in items?

    if(myBag->number_of_item_bag > 0)
    {
        if(myBag->bag_head->item_id == item_id)
        {
            Item *will_delete = myBag->bag_head;

            if(myBag->number_of_item_bag != 1)
            {
                myBag->bag_head->next_item->prev_item = NULL;
                myBag->bag_head = myBag->bag_head->next_item;
            }
            else
            {
                myBag->bag_head = NULL;
            }

            free(will_delete);
            myBag->number_of_item_bag --;
            check_find = 1;
        }
        else if(myBag->bag_tail->item_id == item_id)
        {
            Item *will_delete = myBag->bag_tail;

            if(myBag->number_of_item_bag != 1)
            {
                myBag->bag_tail->prev_item->next_item = NULL;
                myBag->bag_tail = myBag->bag_tail->prev_item;
            }
            else
            {
                myBag->bag_tail = NULL;
            }

            free(will_delete);
            myBag->number_of_item_bag --;
            check_find = 1;
        }
        else
        {
            for (int i = 0; i < myBag->number_of_item_bag; i++)
            {
                if(item_id == item_cursor->item_id)
                {
                    Item *will_delete = item_cursor;

                    item_cursor->prev_item->next_item = item_cursor->next_item;
                    item_cursor->next_item->prev_item = item_cursor->prev_item;

                    free(will_delete);
                    myBag->number_of_item_bag --;
                    check_find = 1;
                }

                item_cursor = item_cursor->next_item;
            }
        }
    }
    
    (check_find == -1) ? printf("=> Dude, there is NOT any item in the bag with id:%d!\n", item_id) : 0;
}

void display_bag(Bag *myBag)
{

    if(myBag->number_of_item_bag > 0)
    {
        Item *cursor = myBag->bag_head;
        printf("\n$$$ Items in bag :\n");

        for (int i = 0; i < myBag->number_of_item_bag; i++)
        {
            printf("%d. id:%d %s (Damage:%d Shield:%d Heal:%d)\n",
                (i+1), cursor->item_id, cursor->item_name, cursor->damage_up, cursor->shield_up, cursor->health_change);
            
            cursor = cursor->next_item;
        }
        
    }
    else
    {
        printf("=> Dude, the bag is empty!!");
    }

}

Item* find_item_bag(int itemId, Bag *myBag)
{

    Item *cursor = myBag->bag_head;

    for (int i = 0; i < myBag->number_of_item_bag; i++)
    {
        if(cursor->item_id == itemId)
        {
            return cursor; // item found
        }
        cursor = cursor->next_item;
    }
    
    return NULL;

}