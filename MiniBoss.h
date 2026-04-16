#pragma once
#include <string>
#include "Monster.h"

using namespace std;

class MiniBoss : public Monster
{
    public:
        MiniBoss(string pname, int health, int attack, int defense, int goal)
            : Monster(pname, health, attack, defense, goal, "MINIBOSS")
        {
        }

        int getMaxActions() const override
        {
            return 3;
        }
};