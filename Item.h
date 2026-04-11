#pragma once
#include <string>
#include <iostream>

using namespace std;

class Item
{
    private:
        string name;
        string type;
        int quantity;
        int value;

    public:
        Item(string itemName, string itemType, int itemValue, int itemQuantity)
        {
            name = itemName;
            type = itemType;
            value = itemValue;
            quantity = itemQuantity;
        }

        string getName()
        {
            return name;
        }

        string getType()
        {
            return type;
        }

        int getValue()
        {
            return value;
        }

        int getQuantity()
        {
            return quantity;
        }

        void setQuantity(int q)
        {
            quantity = q;
        }
};