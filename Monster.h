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
            : Entity(pname, health, attack, defense)
        {
            mercyGauge = 0;
            mercyGoal = goal;
            category = pcategory;
        }

        virtual ~Monster() {}

        virtual int getMaxActions() const = 0;

        virtual string getCategory() const = 0;


        /// @brief Modifie la jauge Mercy et la borne entre 0 et mercyGoal.
        /// Les impacts négatifs (INSULT, THREATEN) peuvent faire descendre la jauge,
        /// ce qui force le joueur à réfléchir avant d'agir.
        /// @param amount Delta à appliquer, positif ou négatif
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


        /// @brief Retourne vrai si la jauge Mercy a atteint l'objectif.
        /// C'est la seule condition pour que l'option MERCY soit utilisable en combat.
        bool isSpareable()
        {
            return mercyGauge >= mercyGoal;
        }


        /// @brief Ajoute un identifiant d'action ACT au monstre, dans la limite de getMaxActions().
        /// Un NORMAL ne peut jamais avoir plus de 2 actions même si le CSV en contient davantage.
        /// @param actionID Identifiant de l'action (doit exister dans le catalogue du GameManager)
        void addAction(string actionID)
        {
            if ((int)availableActions.size() < getMaxActions())
            {
                availableActions.push_back(actionID);
            }
        }

        int getMercyGauge() 
        {
            return mercyGauge;
        }

        int getMercyGoal()  
        {
            return mercyGoal;
        }

        vector<string> getActions()    
        {
            return availableActions;
        }
};