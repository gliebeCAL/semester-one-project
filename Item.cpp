#include "Item.h"
#include <time.h>
#include <iostream>

Item::Item()
{
    //ctor
}

void Item::Generate(int type,int difficulty)
{
    srand(time(NULL));

    itemType = type;

    if (itemType <= 8)
    {
        enchantRoll = rand()%20;

        while (enchantRoll < difficulty)
        {
            //This decides how many enchantments go on an item.
            enchant += 1;

            enchantRoll = rand()%20;
        }
    }
    else if (itemType > 8)
    {
        spellRoll = rand() % 5;

        while (spellRoll == 0)
        {
            spell += 1;
        }
    }


    if (itemType == 0)
    {
        //Weapons
        damage = rand() % ((difficulty*2)+1);
        defense = rand() % (difficulty);

        if (enchant > 0)
        {
            for(int e;e=0;e++)
            {
                enchantEffect = ;
            }
        }
    }
    else if (itemType == 1)
    {
        //Armor (Chest Plate)
        damage = rand() % (difficulty)
        defense = rand() % ((difficulty*2)+1)

        if (enchant > 0)
        {
            for(int e;e=0;e++)
            {
                enchantEffect = ;
            }
        }
    }
    else if (itemType == 2)
    {
        //Armor (Greaves)
        damage = rand() % (difficulty)
        defense = rand() % ((difficulty*2)+1)

        if (enchant > 0)
        {
            for(int e;e=0;e++)
            {
                enchantEffect = ;
            }
        }

    }
    else if (itemType == 3)
    {
        //Armor (Boots)
        damage = rand() % (difficulty)
        defense = rand() % ((difficulty*2)+1)

        if (enchant > 0)
        {
            for(int e;e=0;e++)
            {
                enchantEffect = ;
            }
        }

    }
    else if (itemType == 4)
    {
        //Armor (Gauntlets)
        damage = rand() % (difficulty)
        defense = rand() % ((difficulty*2)+1)

        if (enchant > 0)
        {
            for(int e;e=0;e++)
            {
                enchantEffect = ;
            }
        }

    }
    else if (itemType == 5)
    {
        //Armor (Rings)
        damage = rand() % (difficulty)
        defense = rand() % (difficulty)

        if (enchant > 0)
        {
            for(int e;e=0;e++)
            {
                enchantEffect = ;
            }
        }
    }
    else if (itemType == 6)
    {
        //Armor (Necklace)
        damage = rand() % (difficulty)
        defense = rand() % (difficulty)

        if (enchant > 0)
        {
            for(int e;e=0;e++)
            {
                enchantEffect = ;
            }
        }
    }
    else if (itemType == 7)
    {
        //Armor (Shields)

    }
    else if (itemType == 8)
    {
        //Healing and Buff Items
    }
    else if (itemType == 9)
    {
        //Scrolls
        for (int s;s<spellRoll;s++)
        {
            spellEffect =
        }

        damage = rand() % (difficulty)

    }
    else if (itemType == 10)
    {
        //Wands

        for (int s;s<spellRoll;s++)
        {
            spellEffect =
        }

        damage = rand() % (difficulty)

        if (enchant > 0)
        {
            for(int e;e=0;e++)
            {
                enchantEffect = ;
            }
        }
    }
}
