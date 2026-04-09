#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Entity.h"
#include "Item.h"

using namespace std;

class Player : public Entity
{
private:
    int gold;
    int exp;
    vector<Item*> inventory;

public:
    Player(string playerName)
    {
        name = playerName;
        hpMax = 100;
        hp = 100;
        at = 10;
        de = 5;
        gold = 0;
        exp = 0;
    }

    void addItem(Item* item)
    {
        inventory.push_back(item);
    }

    void useHealItem(int index)
    {
        if (index >= 0 && index < inventory.size())
        {
            hp += inventory[index]->healAmount;
            if (hp > hpMax) hp = hpMax;
            
            inventory.erase(inventory.begin() + index);
        }
    }
};