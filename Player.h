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
    vector<Item*> inventory;
    int monstersSpared;
    int totalVictories;
    int monstersKilled;

public:
    Player(string playerName) : Entity(playerName, 100, 100, 10, 5)
    {
        monstersSpared = 0;
        totalVictories = 0;
        monstersKilled = 0;
    }

    void useItem(int index)
    {
        if (index >= 0 && index < inventory.size())
        {
            hp += inventory[index]->getHealAmount();
            if (hp > hpMax) hp = hpMax;
            inventory.erase(inventory.begin() + index);
        }
    }

    void attack(Entity* target)
    {
        target->takeDamage(at);
    }
    
    void addItem(Item* item)
    {
        inventory.push_back(item);
    }
};