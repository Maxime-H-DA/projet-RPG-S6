#include <iostream>
#include <string>
#include "Player.h"
#include "Monster.h"
#include "NormalMonster.h"
#include "GameManager.h"

using namespace std;

/// @brief Tests automatiques lancés au démarrage avant le menu.
/// Vérifie : réception de dégâts, système Mercy, level up.
/// Le joueur est remis à son état initial après les tests.
/// @param p Pointeur vers le joueur créé dans main()
void runUnitTests(Player* p)
{
    cout << "--- TESTS LOGIQUES ---" << endl;
    NormalMonster dummy("Cible", 50, 10, 5, 20);
    
    int initialHP = p->getHP();
    dummy.attack(p);
    if (p->getHP() < initialHP)
    {
        cout << "Reception degats : OK" << endl;
    }
    p->setHP(p->getHPMax());

    dummy.updateMercy(20);
    if (dummy.isSpareable())
    {
        cout << "Systeme Mercy : OK" << endl;
    }

    int initialLV = p->getLevel();
    p->gainXP(5);
    if(p->getLevel() > initialLV)
    {
        cout << "Test Level Up : OK" << endl;
    }

    p->setlevel(1);
    p->setHPMax(100);
    p->setHP(p->getHPMax());
    p->setAt(30);
    p->setDe(10);

    cout << "----------------------" << endl;
}

int main()
{
    string name;
    cout << "Nom du heros : ";
    cin >> name;

    Player* p = new Player(name);
    GameManager gm(p);

    gm.loadItems("items.csv");
    gm.loadMonsters("monsters.csv");

    runUnitTests(p);
    gm.mainMenu();

    delete p;
    return 0;
}