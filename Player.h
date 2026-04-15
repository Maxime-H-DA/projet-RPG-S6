#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Entity.h"
#include "Item.h"

using namespace std;

class Player : public Entity
{
    private:
        vector<Item*> inventory;
        int monstersKilled;
        int monstersSpared;
        int totalVictories;

    public:
        Player(string playerName) : Entity(playerName, 100, 100, 10, 5)
        {
            monstersKilled = 0;
            monstersSpared = 0;
            totalVictories = 0;
        }

        void useItem(int index)
        {
            if (index < 0 || index >= (int)inventory.size())
            {
                cout << "Index invalide." << endl;
                return;
            }

            Item* item = inventory[index];

            if (item->getType() == "HEAL")
            {
                hp += item->getValue();
                if (hp > hpMax)
                {
                    hp = hpMax;
                }
                cout << "Tu utilises " << item->getName() << " : +" << item->getValue() << " HP." << endl;
            }
            else if (item->getType() == "BUFF_DEF")
            {
                de += item->getValue();
                cout << "Tu utilises " << item->getName() << " : +" << item->getValue() << " DEF." << endl;
            }
            else if (item->getType() == "BUFF_ATK")
            {
                at += item->getValue();
                cout << "Tu utilises " << item->getName() << " : +" << item->getValue() << " ATK." << endl;
            }

            int newQty = item->getQuantity() - 1;
            if (newQty <= 0)
            {
                delete item;
                inventory.erase(inventory.begin() + index);
            }
            else
            {
                item->setQuantity(newQty);
            }
        }

        void showInventory()
        {
            if (inventory.empty())
            {
                cout << "L'inventaire est vide." << endl;
                return;
            }
            for (size_t i = 0; i < inventory.size(); ++i)
            {
                cout << i << ". " << inventory[i]->getName()
                     << " [" << inventory[i]->getType() << "]"
                     << " valeur: " << inventory[i]->getValue()
                     << " qty: " << inventory[i]->getQuantity() << endl;
            }
        }

        void addItem(Item* item)
        {
            inventory.push_back(item);
        }

        int getKilledCount()
        {
            return monstersKilled;
        }

        int getSparedCount()
        {
            return monstersSpared;
        }

        int getTotalVictories()
        {
            return totalVictories;
        }

        void addKill()
        {
            monstersKilled++;
            totalVictories++;
        }

        void addSpare()
        {
            monstersSpared++;
            totalVictories++;
        }
};