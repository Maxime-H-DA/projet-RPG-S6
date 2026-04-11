#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Entity.h"

using namespace std;

class Monster : public Entity
{
private:
    string category;
    int mercyGauge;
    int mercyGoal;
    vector<string> availableActions;

public:
    Monster(string monsterName, int health, int attack, int defense, int goal, string pcategory) 
        : Entity(monsterName, health, health, attack, defense)
    {
        mercyGauge = 0;
        mercyGoal = goal;
        category = pcategory;
    }

    virtual ~Monster()
    {
    }

    void updateMercy(int amount)
    {
        mercyGauge += amount;
        if (mercyGauge < 0) 
        {
            mercyGauge = 0;
        }
        if (mercyGauge > mercyGoal) 
        {
            mercyGauge = mercyGoal;
        }
    }

    void attack(Player* target)
    {
        target->takeDamage(at);
    }

    bool isSpareable()
    {
        return mercyGauge >= mercyGoal;
    }

    string getCategory()
    {
        return category;
    }
    
    void addAction(string actionID)
    {
        availableActions.push_back(actionID);
    }
};