#pragma once
#include <string>
#include "Entity.h"

using namespace std;

class Monster : public Entity
{
private:
    int mercyGauge;
    int mercyGoal;

public:
    Monster(string monsterName, int health, int attack, int defense, int goal)
    {
        name = monsterName;
        hpMax = health;
        hp = health;
        at = attack;
        de = defense;
        mercyGauge = 0;
        mercyGoal = goal;
    }

    bool isSpareable()
    {
        return mercyGauge >= mercyGoal;
    }
};