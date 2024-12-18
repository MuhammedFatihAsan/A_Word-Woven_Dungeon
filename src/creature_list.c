#include "../headers/creature_list.h"

Creature *add_creature_list(Creature_list *creatureList)
{

    Creature *new_creature = (Creature *)malloc(sizeof(Creature));

    if(creatureList->number_of_creature_list == 0)
    {
        creatureList->creature_list_head = new_creature;
        creatureList->creature_list_tail = new_creature;
        creatureList->number_of_creature_list++;
    }
    else
    {
        new_creature->prev_creature = creatureList->creature_list_tail;
        creatureList->creature_list_tail->next_creature = new_creature;
        creatureList->creature_list_tail = new_creature;
        creatureList->number_of_creature_list++;
    }

    return new_creature;
}

void load_creature_infos(Creature_list *creatureList)
{

    FILE *file;
    char line[57]; // Maximum expected number of characters with safety margin

    file = fopen(GAME_DATA_PATH "creatures.txt", "r");

    if(file == NULL)
    {
        perror("Can't find creatures.txt");
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
        int creature_data[4];
        int counter = 0;
        while(token != NULL && counter < 4) // double safety, info number must 3 and token must NULL
        {
            creature_data[counter] = atoi(token); // convert to int
            counter++;
            token = strtok(NULL, "/");
        }

        // create new creature and add to list. load infos to new creature infos
        Creature *load_creature = add_creature_list(creatureList); 

        for (int i = 0; i < 4; i++)
        {
            switch (i)
            {
                case 0:
                    load_creature->creature_id = creature_data[i];
                    break;
                case 1:
                    load_creature->creature_health = creature_data[i];
                    break;
                case 2:
                    load_creature->creature_damage = creature_data[i];
                    break;
                case 3:
                    load_creature->item_id = creature_data[i];
                    break;
            }
        }
        
    }

    fclose(file);

}

Creature* find_creature_creatureList(int creatureId, Creature_list *creatureList)
{
    if(creatureId == -1){return NULL;}

    Creature *cursor = creatureList->creature_list_head;

    for (int i = 0; i < creatureList->number_of_creature_list; i++)
    {
        if(cursor->creature_id == creatureId)
        {
            return cursor; // creature found
        }
        cursor = cursor->next_creature;
    }

    printf("# The id:%d you are looking for is not in creature list\n",creatureId);
    return NULL;
}