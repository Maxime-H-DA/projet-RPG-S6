#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Player.h"
#include "Monster.h"
#include "ActAction.h"

using namespace std;

class GameManager
{
private:
    Player* player;
    vector<Monster*> bestiary;
    map<string, ActAction> actionCatalog;

public:
    GameManager(Player* p)
    {
        player = p;
    }

    void loadItems(string filename)
    {
        // Logique de lecture items.csv
    }

    void loadMonsters(string filename)
    {
        // Logique de lecture monsters.csv
    }

    void startCombat()
    {
        // Logique du combat au tour par tour
    }

    void mainMenu()
    {
        // Affichage Bestiaire, Stats, Items, Combat
    }

    void checkEndCondition()
    {
        // Vérifie si le joueur a gagné ou perdu
    }

    void announceBattle(Monster* m)
    {
        cout << "BATAILLE : " << player->getName() << " VS " << m->getName() << endl;
    }
};