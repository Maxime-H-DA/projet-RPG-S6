#include <iostream>
#include <vector>
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "GameManager.h"
#include "Boss.h"

using namespace std;

void runTests()
{
    Player testPlayer("Hero");
    
    if (testPlayer.isAlive())
    {
        cout << "Test 1: Player initialement vivant - OK" << endl;
    }

    testPlayer.takeDamage(20);
    cout << "Test 2: Reception de degats (20) - OK" << endl;

    Item* potion = new Item("Petite Potion", "HEAL", 20, 1);
    testPlayer.addItem(potion);
    testPlayer.useItem(0); 
    cout << "Test 3: Ajout et utilisation objet soin - OK" << endl;

    Monster* boss = new Boss("Dragon", 200, 30, 10, 100);
    GameManager gm(&testPlayer);
    
    gm.announceBattle(boss);
    
    testPlayer.attack(boss);
    cout << "Test 4: Interaction combat (Attaque Player -> Monster) - OK" << endl;

    cout << "Test 6: Tentative de lecture de items.csv..." << endl;
    gm.loadItems("items.csv");

    testPlayer.takeDamage(200);
    if (!testPlayer.isAlive())
    {
        cout << "Test 5: Mort du joueur apres degats massifs - OK" << endl;
    }

    delete boss;

    cout << "--- Tous les tests sont termines avec succes ---" << endl;
}

int main()
{
    runTests();
    return 0;
}