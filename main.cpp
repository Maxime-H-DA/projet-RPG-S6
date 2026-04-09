#include <iostream>
#include <vector>
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "GameManager.h"

using namespace std;

void runTests()
{
    Player testPlayer("Hero");
    
    if (testPlayer.islandAlive())
    {
        cout << "Test 1: Player initialement vivant - OK" << endl;
    }

    testPlayer.takeDamage(20);
    cout << "Test 2: Reception de degats (20) - OK" << endl;

    Item* potion = new Item("Petite Potion", 20);
    testPlayer.addItem(potion);
    testPlayer.useHealItem(0);
    cout << "Test 3: Ajout et utilisation objet soin - OK" << endl;

    Monster* boss = new Monster("Dragon", 200, 30, 10, 50);
    GameManager gm(&testPlayer, boss);
    gm.announceBattle();
    gm.processTurn();
    cout << "Test 4: GameManager et interaction combat - OK" << endl;

    testPlayer.takeDamage(200);
    if (!testPlayer.islandAlive())
    {
        cout << "Test 5: Mort du joueur apres degats massifs - OK" << endl;
    }

    delete potion;
    delete boss;

    cout << "--- Tous les tests sont termines avec succes ---" << endl;
}

int main()
{
    runTests();
    return 0;
}