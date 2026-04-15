#pragma once
#include <string>
#include <iostream>

using namespace std;

class Item
{
    private:
        string name;
        string type;
        int value;
        int quantity;

    public:
        Item(string pname, string ptype, int pvalue, int pquantity)
        {
            name = pname;
            type = ptype;
            value = pvalue;
            quantity = pquantity;
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