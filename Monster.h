#pragma once
#include <string>
#include <vector>
#include "Entity.h"

using namespace std;

class Monster : public Entity
{
    private:
        int mercyGauge;
        int mercyGoal;
        string category;


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

        virtual void showActions() = 0;

        virtual ~Monster() 
        {
        }

        bool isSpareable()
        {
            return mercyGauge >= mercyGoal;
        }

        string getCategory()
        {
            return category;
        }

        void setCategory(string c)
        {
            category = c;
        }

};