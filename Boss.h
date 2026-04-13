#pragma once
#include <iostream>
#include <string>
#include "Monster.h"

using namespace std;

class Boss : public Monster
{
    public:
        Boss(string bossName, int health, int attack, int defense, int goal) 
            : Monster(bossName, health, attack, defense, goal, "BOSS")
        {
        }

    };