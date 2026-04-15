#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Player.h"
#include "Monster.h"
#include "GameManager.h"
#include "NormalMonster.h"
#include "Boss.h"

using namespace std;

void runUnitTests(Player* p)
{
    cout << "--- VERIFICATION TECHNIQUE ---" << endl;

    if (p->isAlive())
    {
        cout << "[OK] Player initialisation" << endl;
    }

    NormalMonster testM("TestDummy", 10, 5, 2, 50);
    testM.updateMercy(30);
    if (!testM.isSpareable())
    {
        cout << "[OK] Mercy : jauge < objectif => pas epargneable" << endl;
    }

    testM.updateMercy(30);
    if (testM.isSpareable())
    {
        cout << "[OK] Mercy : jauge >= objectif => epargneable" << endl;
    }

    int initialHP = p->getHP();
    testM.attack(p);
    if (p->getHP() <= initialHP)
    {
        cout << "[OK] Combat : degats recus correctement" << endl;
    }

    cout << "------------------------------\n" << endl;
}

int main()
{
    srand(time(0));

    string name;
    cout << "Bienvenue dans ALTERDUNE" << endl;
    cout << "Entrez votre nom de heros : ";
    cin >> name;

    Player* p = new Player(name);
    GameManager gm(p);

    gm.loadItems("items.csv");
    gm.loadMonsters("monsters.csv");

    gm.displayStartSummary();

    runUnitTests(p);

    gm.mainMenu();

    delete p;
    return 0;
}