#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Entity.h"

using namespace std;

class Monster : public Entity
{
    private:
        string category;
        int mercyGauge;
        int mercyGoal;
        vector<string> availableActions;

    public:
        Monster(string pname, int health, int attack, int defense, int goal, string pcategory)
            : Entity(pname, health, health, attack, defense)
        {
            mercyGauge = 0;
            mercyGoal = goal;
            category = pcategory;
        }

        virtual ~Monster() {}

        void updateMercy(int amount)
        {
            mercyGauge += amount;
            if (mercyGauge < 0)
            {
                mercyGauge = 0;
            }
            if (mercyGauge > mercyGoal)
            {
                mercyGauge = mercyGoal;
            }
        }

        bool isSpareable()
        {
            return mercyGauge >= mercyGoal;
        }

        string getCategory()
        {
            return category;
        }

        int getMercyGauge()
        {
            return mercyGauge;
        }

        int getMercyGoal()
        {
            return mercyGoal;
        }

        void addAction(string actionID)
        {
            availableActions.push_back(actionID);
        }

        vector<string> getActions()
        {
            return availableActions;
        }
};