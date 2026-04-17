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

        string getCategory() const override
        {
            return "BOSS";
        }

        int getMaxActions() const override
        {
            return 4;
        }

        void attack(Entity* target) override
        {
            int base = getAt() - target->getDe();
            if (base < 1) base = 1;
            uniform_int_distribution<int> dist(base * 2, base * 4);
            int damage = dist(rng);
            cout << getName() << " attaque pour " << damage << " degats !" << endl;
            target->takeDamage(damage); 
        }
};