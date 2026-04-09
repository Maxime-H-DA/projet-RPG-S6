#pragma once
#include <string>

using namespace std;

class Item
{
public:
    string name;
    int healAmount;

    Item(string itemName, int amount)
    {
        name = itemName;
        healAmount = amount;
    }
};