#pragma once
#include <string>
#include "Monster.h"

using namespace std;

class Boss : public Monster
{
    public:
        Boss(string pname, int health, int attack, int defense, int goal)
            : Monster(pname, health, attack, defense, goal, "BOSS")
        {
        }
};