#pragma once
#include <string>

using namespace std;

class Item
{
    private:
        string name;
        int healAmount;
    public:

        Item(string itemName, int amount)
        {
            name = itemName;
            healAmount = amount;
        }
        
        string getName()
        {
            return name;
        }

        int getHealAmount()
        {
            return healAmount;
        }
};