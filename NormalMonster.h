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

        string getCategory() const override
        {
            return "NORMAL";
        }

        int getMaxActions() const override
        {
            return 2;
        }


        /// @brief Attaque faible : fourchette (1, base). On s'éloigne du sujet (rand 0, HPmax cible)
        /// pour garder une cohérence ATK/DEF. Un NORMAL inflige peu, ce qui laisse
        /// le joueur se soigner ou faire monter la Mercy sans trop de pression.
        /// @param target Entité ciblée
        void attack(Entity* target) override
        {
            int base = getAt() - target->getDe();
            if (base < 1) base = 1;
            uniform_int_distribution<int> dist(1, base);
            int damage = dist(rng);
            cout << getName() << " attaque pour " << damage << " degats !" << endl;
            target->takeDamage(damage); 
        }
};