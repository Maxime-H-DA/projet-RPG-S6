#pragma once
#include <string>
#include "Monster.h"

using namespace std;

class NormalMonster : public Monster
{
    public:
        NormalMonster(string pname, int health, int attack, int defense, int goal)
            : Monster(pname, health, attack, defense, goal, "NORMAL")
        {
        }
};