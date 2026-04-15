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
#include "MiniBoss.h"
#include "ActAction.h"

using namespace std;

struct BestiaryEntry
{
    string name;
    string category;
    int hpMax;
    int at;
    int de;
    string result;
};

class GameManager
{
    private:
        Player* player;
        vector<Monster*> bestiary;
        vector<BestiaryEntry> defeatedLog;
        map<string, ActAction> actionCatalog;

    public:
        GameManager(Player* p)
        {
            player = p;

            actionCatalog["JOKE"]      = ActAction("JOKE",      "Tu racontes une blague nulle. Le monstre rit quand meme !", 20);
            actionCatalog["COMPLIMENT"]= ActAction("COMPLIMENT","Tu flattes le monstre sur sa coiffure.", 15);
            actionCatalog["DANCE"]     = ActAction("DANCE",     "Tu fais le robot. Le monstre est gene pour toi.", 10);
            actionCatalog["PET"]       = ActAction("PET",       "Tu le grattes derriere l'oreille. Il ronronne.", 25);
            actionCatalog["DISCUSS"]   = ActAction("DISCUSS",   "Tu parles meteo. Le monstre baille.", 5);
            actionCatalog["OBSERVE"]   = ActAction("OBSERVE",   "Tu fixes le monstre en silence. Malaise.", 0);
            actionCatalog["INSULT"]    = ActAction("INSULT",    "Tu es odieux. Le monstre est offense !", -15);
            actionCatalog["THREATEN"]  = ActAction("THREATEN",  "Tu brandis le poing. Le monstre se met en colere !", -10);
        }

        void displayStartSummary()
        {
            cout << "\n=== BIENVENUE DANS ALTERDUNE ===" << endl;
            cout << "Heros : " << player->getName() << endl;
            cout << "HP    : " << player->getHP() << " / " << player->getHPMax() << endl;
            cout << "Inventaire de depart :" << endl;
            player->showInventory();
            cout << "================================\n" << endl;
        }

        void loadItems(string filename)
        {
            ifstream file(filename);
            if (!file.is_open())
            {
                cout << "Erreur : impossible d'ouvrir " << filename << endl;
                return;
            }

            string line;
            getline(file, line);

            while (getline(file, line))
            {
                stringstream ss(line);
                string category, name, type, valStr, qtyStr;

                getline(ss, category, ';');
                getline(ss, name, ';');
                getline(ss, type, ';');
                getline(ss, valStr, ';');
                getline(ss, qtyStr, ';');

                if (name.empty() || type.empty() || valStr.empty() || qtyStr.empty())
                {
                    cout << "Ligne ignoree (mal formee) : " << line << endl;
                    continue;
                }

                try
                {
                    Item* newItem = new Item(name, type, stoi(valStr), stoi(qtyStr));
                    player->addItem(newItem);
                }
                catch (...)
                {
                    cout << "Ligne ignoree (erreur de valeur) : " << line << endl;
                }
            }
            file.close();
        }

        void loadMonsters(string filename)
        {
            ifstream file(filename);
            if (!file.is_open())
            {
                cout << "Erreur : impossible d'ouvrir " << filename << endl;
                return;
            }

            string line;
            getline(file, line);

            while (getline(file, line))
            {
                stringstream ss(line);
                string category, name, hp, hpActuel, at, de, act;

                getline(ss, category, ';');
                getline(ss, name, ';');
                getline(ss, hp, ';');
                getline(ss, hpActuel, ';');
                getline(ss, at, ';');
                getline(ss, de, ';');

                if (category.empty() || name.empty() || hp.empty())
                {
                    cout << "Ligne ignoree (mal formee) : " << line << endl;
                    continue;
                }

                Monster* m = nullptr;

                try
                {
                    int mercyGoal = 100;
                    if (category == "NORMAL")
                    {
                        m = new NormalMonster(name, stoi(hp), stoi(at), stoi(de), mercyGoal);
                    }
                    else if (category == "MiniBoss")
                    {
                        m = new MiniBoss(name, stoi(hp), stoi(at), stoi(de), mercyGoal);
                    }
                    else if (category == "Boss")
                    {
                        m = new Boss(name, stoi(hp), stoi(at), stoi(de), mercyGoal);
                    }
                }
                catch (...)
                {
                    cout << "Ligne ignoree (erreur de valeur) : " << line << endl;
                    continue;
                }

                if (m != nullptr)
                {
                    while (getline(ss, act, ';'))
                    {
                        if (!act.empty() && act != "-")
                        {
                            m->addAction(act);
                        }
                    }
                    bestiary.push_back(m);
                }
            }
            file.close();
        }

        void startCombat(Monster* enemy)
        {
            cout << "\n=== BATAILLE : " << player->getName() << " VS " << enemy->getName() << " ===" << endl;

            bool combatOver = false;
            string combatResult = "";

            while (player->isAlive() && enemy->isAlive() && !combatOver)
            {
                cout << "\n[" << player->getName() << " HP: " << player->getHP() << "/" << player->getHPMax() << "]"
                     << "  [" << enemy->getName() << " HP: " << enemy->getHP() << "/" << enemy->getHPMax() << "]"
                     << "  [Mercy: " << enemy->getMercyGauge() << "/" << enemy->getMercyGoal() << "]" << endl;

                cout << "--- TOUR DE " << player->getName() << " ---" << endl;
                cout << "1. FIGHT  2. ACT  3. ITEM  4. MERCY" << endl;

                int choice;
                cin >> choice;

                if (choice == 1)
                {
                    player->attack(enemy);
                    if (!enemy->isAlive())
                    {
                        player->addKill();
                        cout << enemy->getName() << " est mort !" << endl;
                        combatResult = "Tue";
                        combatOver = true;
                    }
                }
                else if (choice == 2)
                {
                    vector<string> acts = enemy->getActions();
                    if (acts.empty())
                    {
                        cout << "Aucune action disponible pour ce monstre." << endl;
                    }
                    else
                    {
                        for (size_t i = 0; i < acts.size(); ++i)
                        {
                            cout << i << ". " << acts[i] << endl;
                        }
                        int actChoice;
                        cin >> actChoice;
                        if (actChoice >= 0 && (size_t)actChoice < acts.size())
                        {
                            string id = acts[actChoice];
                            if (actionCatalog.count(id))
                            {
                                cout << actionCatalog[id].getText() << endl;
                                enemy->updateMercy(actionCatalog[id].getImpact());
                            }
                            else
                            {
                                cout << "Action inconnue dans le catalogue." << endl;
                            }
                        }
                    }
                }
                else if (choice == 3)
                {
                    player->showInventory();
                    cout << "Quel objet utiliser ? (-1 pour annuler) : ";
                    int itemIdx;
                    cin >> itemIdx;
                    if (itemIdx != -1)
                    {
                        player->useItem(itemIdx);
                    }
                }
                else if (choice == 4)
                {
                    if (enemy->isSpareable())
                    {
                        player->addSpare();
                        cout << "Tu as epargne " << enemy->getName() << " !" << endl;
                        combatResult = "Epargne";
                        combatOver = true;
                    }
                    else
                    {
                        cout << "Le monstre refuse d'etre epargne. (Mercy insuffisante)" << endl;
                    }
                }

                if (enemy->isAlive() && !combatOver)
                {
                    enemy->attack(player);
                }
            }

            if (!player->isAlive())
            {
                cout << "\nTu as ete vaincu... GAME OVER." << endl;
                exit(0);
            }

            if (!combatResult.empty())
            {
                BestiaryEntry entry;
                entry.name     = enemy->getName();
                entry.category = enemy->getCategory();
                entry.hpMax    = enemy->getHPMax();
                entry.at       = enemy->getAt();
                entry.de       = enemy->getDe();
                entry.result   = combatResult;
                defeatedLog.push_back(entry);
            }

            if (player->getTotalVictories() >= 10)
            {
                checkEnding();
            }
        }

        void checkEnding()
        {
            cout << "\n*** FIN DU JEU ***" << endl;
            if (player->getSparedCount() == 10)
            {
                cout << "FIN PACIFISTE : Tu as apporte la paix !" << endl;
            }
            else if (player->getKilledCount() == 10)
            {
                cout << "FIN GENOCIDAIRE : Tu as aneanti tout le monde..." << endl;
            }
            else
            {
                cout << "FIN NEUTRE : Tes choix ont ete ambigus." << endl;
            }
            exit(0);
        }

        void showDefeatedBestiary()
        {
            if (defeatedLog.empty())
            {
                cout << "Aucun monstre vaincu pour l'instant." << endl;
                return;
            }
            cout << "\n--- BESTIAIRE (monstres vaincus) ---" << endl;
            for (const BestiaryEntry& e : defeatedLog)
            {
                cout << "- " << e.name
                     << " [" << e.category << "]"
                     << "  HP max: " << e.hpMax
                     << "  ATK: " << e.at
                     << "  DEF: " << e.de
                     << "  => " << e.result << endl;
            }
        }

        void mainMenu()
        {
            int choice = 0;
            while (choice != 5 && player->isAlive())
            {
                cout << "\n--- MENU PRINCIPAL ---" << endl;
                cout << "Victoires : " << player->getTotalVictories() << "/10" << endl;
                cout << "1. Partir au combat" << endl;
                cout << "2. Inventaire / Utiliser un objet" << endl;
                cout << "3. Statistiques" << endl;
                cout << "4. Bestiaire" << endl;
                cout << "5. Quitter" << endl;
                cin >> choice;

                if (choice == 1)
                {
                    if (!bestiary.empty())
                    {
                        int randomIdx = rand() % bestiary.size();
                        startCombat(bestiary[randomIdx]);
                    }
                    else
                    {
                        cout << "Aucun monstre charge." << endl;
                    }
                }
                else if (choice == 2)
                {
                    player->showInventory();
                    cout << "Numero de l'objet a utiliser (-1 pour annuler) : ";
                    int itemIdx;
                    cin >> itemIdx;
                    if (itemIdx != -1)
                    {
                        player->useItem(itemIdx);
                    }
                }
                else if (choice == 3)
                {
                    cout << "\n--- STATS DE " << player->getName() << " ---" << endl;
                    cout << "HP       : " << player->getHP() << " / " << player->getHPMax() << endl;
                    cout << "ATK      : " << player->getAt() << endl;
                    cout << "DEF      : " << player->getDe() << endl;
                    cout << "Tues     : " << player->getKilledCount() << endl;
                    cout << "Epargnes : " << player->getSparedCount() << endl;
                    cout << "Victoires: " << player->getTotalVictories() << " / 10" << endl;
                }
                else if (choice == 4)
                {
                    showDefeatedBestiary();
                }
            }
        }
};