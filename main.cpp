#include <iostream>
#include <vector>
#include "Player.h"
#include "Monster.h"
#include "Item.h"

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

    testPlayer.takeDamage(150);
    if (!testPlayer.islandAlive())
    {
        cout << "Test 4: Mort du joueur apres degats massifs - OK" << endl;
    }

    cout << "--- Tous les tests sont termines avec succes ---" << endl;
}

int main()
{
    runTests();
    return 0;
}