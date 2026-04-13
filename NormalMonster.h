#pragma once
#include <iostream>
#include <string>
#include "Monster.h"

using namespace std;

class NormalMonster : public Monster
{
        public:
            NormalMonster(string monsterName, int health, int attack, int defense, int goal) : Monster(monsterName, health, attack, defense, goal, "Normal")
            {
            }
};