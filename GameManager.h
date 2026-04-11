#pragma once
#include <iostream>
#include <string>
#include "Player.h"
#include "Monster.h"

using namespace std;

class GameManager
{
    private:
        Player* player;
        Monster* currentMonster;

    public:
        GameManager(Player* p, Monster* m)
        {
            player = p;
            currentMonster = m;
        }

        void announceBattle()
        {
            cout << "BATAILLE : " << player->getName() << " VS " << currentMonster->getName() << endl;
        }

        void processTurn()
        {
            currentMonster->takeDamage(15);
            cout << "Le joueur attaque " << currentMonster->getName() << endl;
        }
};