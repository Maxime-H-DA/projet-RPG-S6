#pragma once
#include <string>
#include "Monster.h"

using namespace std;

class Boss : public Monster
{
    public:
        Boss(string bossName, int health, int attack, int defense, int goal) : Monster(bossName, health, attack, defense, goal)
        {
            setCategory("Boss");
        }

        void showActions()
        {
            cout << "Actions disponibles pour " << name << " :" << endl;
            cout << "1. Attaque puissante" << endl;
            cout << "2. Défense renforcée" << endl;
            cout << "3. Provocation" << endl;
        }
};