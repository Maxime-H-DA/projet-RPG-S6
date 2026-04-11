#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "Player.h"
#include "Monster.h"
#include "NormalMonster.h"
#include "Boss.h"
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
        
        actionCatalog["JOKE"] = ActAction("JOKE", "Tu racontes une blague. Le monstre rit !", 20);
        actionCatalog["COMPLIMENT"] = ActAction("COMPLIMENT", "Tu flattes le monstre.", 15);
        actionCatalog["DANCE"] = ActAction("DANCE", "Tu danses. Le monstre est amuse.", 10);
        actionCatalog["PET"] = ActAction("PET", "Tu le caresses.", 25);
        actionCatalog["DISCUSS"] = ActAction("DISCUSS", "Tu parles de la pluie.", 5);
        actionCatalog["OBSERVE"] = ActAction("OBSERVE", "Tu regardes le monstre.", 0);
        actionCatalog["INSULT"] = ActAction("INSULT", "Tu es impoli. Le monstre s'enerve !", -15);
        actionCatalog["THREATEN"] = ActAction("THREATEN", "Tu cries. Le monstre a peur.", -10);
    }

    void loadItems(string filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Erreur : Impossible d'ouvrir " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string name, type, valStr, qtyStr;

            getline(ss, name, ';');
            getline(ss, type, ';');
            getline(ss, valStr, ';');
            getline(ss, qtyStr, ';');

            if (!name.empty())
            {
                Item* newItem = new Item(name, type, stoi(valStr), stoi(qtyStr));
                player->addItem(newItem);
                cout << "Item charge : " << name << endl;
            }
        }
        file.close();
    }


    void loadMonsters(string filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Erreur : Impossible d'ouvrir " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string category, name, hp, at, de, goal, act;

            getline(ss, category, ';');
            getline(ss, name, ';');
            getline(ss, hp, ';');
            getline(ss, at, ';');
            getline(ss, de, ';');
            getline(ss, goal, ';');

            Monster* m = nullptr;

            if (category == "NORMAL")
            {
                m = new NormalMonster(name, stoi(hp), stoi(at), stoi(de), stoi(goal));
            }
            else if (category == "BOSS")
            {
                m = new Boss(name, stoi(hp), stoi(at), stoi(de), stoi(goal));
            }

            if (m != nullptr)
            {
                while (getline(ss, act, ';'))
                {
                    if (!act.empty()) 
                    {
                        m->addAction(act);
                    }
                }
                bestiary.push_back(m);
                cout << "Monstre charge : " << name << " (" << category << ")" << endl;
            }
        }
        file.close();
    }

    void announceBattle(Monster* m)
    {
        cout << "BATAILLE : " << player->getName() << " VS " << m->getName() << endl;
    }
};