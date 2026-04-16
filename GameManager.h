#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <limits>
#include "Player.h"
#include "Monster.h"
#include "NormalMonster.h"
#include "MiniBoss.h"
#include "Boss.h"
#include "ActAction.h"

using namespace std;

struct BestiaryEntry
{
    string name;
    string category;
    int hpMax;
    string result;
};

class GameManager
{
    private:
        Player* player;
        vector<Monster*> bestiary;
        vector<BestiaryEntry> defeatedLog;
        map<string, ActAction> actionCatalog;
        bool gameRunning;
        int totalEncounters = 0;
        int lastMiniBossTurn = -5;

        void flushInput()
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    public:
        GameManager(Player* p)
        {
            player = p;
            actionCatalog["JOKE"] = ActAction("JOKE", "Le monstre explose de rire.", 20);
            actionCatalog["COMPLIMENT"] = ActAction("COMPLIMENT", "Le monstre rougit.", 15);
            actionCatalog["DANCE"] = ActAction("DANCE", "Le monstre danse avec vous.", 10);
            actionCatalog["PET"] = ActAction("PET", "Le monstre ronronne.", 25);
            actionCatalog["DISCUSS"] = ActAction("DISCUSS", "Le monstre vous ecoute.", 5);
            actionCatalog["OBSERVE"] = ActAction("OBSERVE", "Le monstre est intrigue.", 0);
            actionCatalog["INSULT"] = ActAction("INSULT", "Le monstre s'enerve.", -15);
            actionCatalog["THREATEN"] = ActAction("THREATEN", "Le monstre tremble.", -10);
            gameRunning = true;
        }

        ~GameManager()
        {
            for (Monster* m : bestiary)
            {
                delete m;
            }
        }

        void loadItems(string filename)
        {
            ifstream file(filename);
            if (!file.is_open())
            {
                return;
            }
            string line;
            while (getline(file, line))
            {
                if (line.empty())
                {
                    continue;
                }
                stringstream ss(line);
                string n, t, v, q;
                if (getline(ss, n, ';') && getline(ss, t, ';') && getline(ss, v, ';') && getline(ss, q, ';'))
                {
                    try 
                    {
                        player->addItem(new Item(n, t, stoi(v), stoi(q)));
                    }
                    catch (...)
                    {
                        cerr << "Erreur de formatage sur la ligne : " << line << endl;
                    }
                }
            }
        }

        void loadMonsters(string filename)
        {
            ifstream file(filename);
            if (!file.is_open())
            {
                return;
            }

            string line;
            while (getline(file, line))
            {
                if (line.empty())
                {
                    continue;
                }
                stringstream ss(line);
                string cat, n, h, a, d, g, act1, act2, act3;

                if (getline(ss, cat, ';') && getline(ss, n, ';') && getline(ss, h, ';') && 
                    getline(ss, a, ';') && getline(ss, d, ';') && getline(ss, g, ';'))
                    {
                        try
                        {
                            Monster* m = nullptr;
                            if (cat == "NORMAL")
                            {
                                m = new NormalMonster(n, stoi(h), stoi(a), stoi(d), stoi(g));
                            }
                            else if (cat == "MINIBOSS")
                            {
                                m = new MiniBoss(n, stoi(h), stoi(a), stoi(d), stoi(g));
                            }
                            else if (cat == "BOSS")
                            {
                                m = new Boss(n, stoi(h), stoi(a), stoi(d), stoi(g));
                            }

                            if (m)
                            {
                                while (getline(ss, act1, ';'))
                                {
                                    if (!act1.empty())
                                    {
                                        m->addAction(act1);
                                    }
                                }
                                bestiary.push_back(m);
                            }
                    }
                    catch (...)
                    {
                        cerr << "Erreur sur la ligne monstre : " << line << endl;
                    }
                }
            }
        }

        void startCombat(Monster* enemy)
        {
            cout << "\n--- Combat : " << enemy->getName() << " ---" << endl;
            cout << "   CATEGORIE : " << enemy->getCategory() << endl;
            bool over = false;
            string finalStatus = "En cours";

            while (player->isAlive() && enemy->isAlive() && !over)
            {
                cout << "\n" << player->getName() << " HP: " << player->getHP() << "/" << player->getHPMax() << endl;
                cout << enemy->getName() << " HP: " << enemy->getHP() << " Mercy: " << enemy->getMercyGauge() << "/" << enemy->getMercyGoal() << endl;
                cout << "1. FIGHT | 2. ACT | 3. ITEM | 4. MERCY" << endl;
                
                int choice;
                if (!(cin >> choice))
                {
                    flushInput();
                    continue;
                }

                if (choice == 1)
                {
                    player->attack(enemy);
                    if (!enemy->isAlive()) 
                    { 
                        player->addKill(enemy->getCategory()); 
                        finalStatus = "Tue"; 
                        over = true; 
                    }
                }
                else if (choice == 2)
                {
                    vector<string> acts = enemy->getActions();
                    for (int i = 0; i < (int)acts.size(); ++i)
                    {
                        cout << i << ". " << acts[i] << endl;
                    }
                    int actIdx;
                    cin >> actIdx;
                    if (actIdx >= 0 && actIdx < (int)acts.size())
                    {
                        ActAction a = actionCatalog[acts[actIdx]];
                        cout << "> " << a.getText() << endl;
                        enemy->updateMercy(a.getImpact());
                    }
                }
                else if (choice == 3)
                {
                    player->showInventory();
                    int idx;
                    cin >> idx;
                    player->useItem(idx);
                }
                else if (choice == 4)
                {
                    if (enemy->isSpareable()) 
                    { 
                        player->addSpare(); 
                        finalStatus = "Epargne"; 
                        cout << enemy->getName() << " baisse sa garde et quitte le combat sans rancune." << endl;
                        over = true; 
                    }
                    else 
                    {
                        cout << enemy->getName() << " ne semble pas encore pret a vous pardonner." << endl;
                    }
                }

                if (enemy->isAlive() && !over)
                {
                    enemy->attack(player);
                }
            }

            defeatedLog.push_back({enemy->getName(), enemy->getCategory(), enemy->getHPMax(), finalStatus});

            if (!player->isAlive()) 
            { 
                cout << "\n--- VOUS AVEZ ECHOUE ---" << endl;
                saveHistory(); 
                gameRunning = false;
            }
            
            if (player->getTotalVictories() >= 10)
            {
                checkEnding();
            }
        }

        void checkEnding()
        {
            cout << "\n--- DESTIN D'ALTERDUNE ---" << endl;
            if (player->getSparedCount() == 10)
            {
                cout << "FIN PACIFISTE : Vous avez apporte la paix." << endl;
            }
            else if (player->getKilledCount() == 10)
            {
                cout << "FIN GENOCIDAIRE : Il ne reste plus rien." << endl;
            }
            else
            {
                cout << "FIN NEUTRE : Le monde reste en equilibre." << endl;
            }
            saveHistory();
            gameRunning = false;
        }

        void saveHistory()
        {
            ofstream out("history.txt");
            out << "HISTORIQUE D'ALTERDUNE" << endl;
            for (auto& e : defeatedLog)
            {
                out << e.name << " [" << e.category << "] : " << e.result << endl;
            }
            out.close();
        }

        void mainMenu()
        {
            cout << "   DEBUT DE L'AVENTURE" << endl;
            cout << "Heros : " << player->getName() << endl;
            cout << "HP    : " << player->getHP() << "/" << player->getHPMax() << endl;
            cout << "ATK   : " << player->getAt() << " | DEF : " << player->getDe() << endl;
            cout << "Inventaire de depart :" << endl;
            player->showInventory();
            int choice = 0;
            while (gameRunning && choice != 5)
            {
                cout << "\n--- MENU (Victories: " << player->getTotalVictories() << "/10) ---" << endl;
                cout << "1. Explorer\n2. Inventaire\n3. Profil\n4. Journal\n5. Quitter" << endl;
                if (!(cin >> choice)) 
                { 
                    flushInput(); 
                    continue; 
                }
                
            if (choice == 1 && !bestiary.empty())
            {
                totalEncounters++; 
                vector<Monster*> validMonsters;

                if (player->getTotalVictories() >= 7) 
                {
                    for (Monster* m : bestiary)
                    {
                        if (m->getCategory() == "BOSS")
                        {
                            validMonsters.push_back(m);
                        }
                    }
                }
                else 
                {
                    for (Monster* m : bestiary) 
                    {
                        string cat = m->getCategory();
                        if (cat == "BOSS")
                        {
                            continue;
                        }
                        if (cat == "MINIBOSS" && totalEncounters <= 3)
                        {
                            continue;
                        }
                        validMonsters.push_back(m);
                    }
                }

                if (validMonsters.empty())
                {
                    validMonsters = bestiary;
                }

                uniform_int_distribution<int> d(0, (int)validMonsters.size() - 1);
                Monster* selected = validMonsters[d(rng)];

                if (selected->getCategory() == "MINIBOSS")
                {
                    lastMiniBossTurn = totalEncounters;
                }

                selected->setHP(selected->getHPMax());
                selected->updateMercy(0); 
                startCombat(selected);
            }
                else if (choice == 2) 
                {
                    player->showInventory();
                }
                else if (choice == 3) 
                {
                    cout << "Kills: " << player->getKilledCount() << " | Spares: " << player->getSparedCount() << " | LV: " << player->getLevel() << endl;
                    cout << "HP: " << player->getHP() << "/" << player->getHPMax() << " | ATK: " << player->getAt() << " | DEF: " << player->getDe() << endl;
                }
                else if (choice == 4)
                {
                    for (auto& e : defeatedLog) 
                    {
                        cout << e.name << " (" << e.result << ")" << endl;
                    }
                }
                else if (choice == 5)
                {
                    gameRunning = false;
                }
            }
            saveHistory();
        }
};