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
        int level;
        int xp;

    public:
        Player(string playerName) : Entity(playerName, 100, 100, 100)
        {
            monstersKilled = 0;
            monstersSpared = 0;
            totalVictories = 0;
            level = 1;
            xp = 0;
        }

        ~Player()
        {
            for (Item* item : inventory)
            {
                delete item;
            }
            inventory.clear();
        }

        virtual void attack(Entity* target) override
        {
            int base = at - target->getDe();
            if (base < 1)
            {
                base = 1;
            }

            float multiplier = 1.0;

            if (target->getCategory() == "BOSS")
            {
                multiplier = 0.8; 
            }
            else if (target->getCategory() == "MINIBOSS")
            {
                multiplier = 1.0; 
            }
            else if (target->getCategory() == "NORMAL")
            {
                multiplier = 1.2;
            }
            uniform_int_distribution<int> dist(base, base * multiplier);
            int damage = dist(rng);
            cout << name << " attaque pour " << damage << " degats !" << endl;
            target->takeDamage(damage);
        }

        string getCategory() const override
        {
            return "PLAYER";
        }

        void gainXP(int amount)
        {
            xp += amount;
            int xpNeeded = 3;
            while (xp >= xpNeeded)
            {
                xp -= xpNeeded;
                level++;
                at += 5;
                de += 5;
                hpMax += 10;
                hp = hpMax;
                cout << "\n*** LEVEL UP ! Niveau " << level << " ***" << endl;
                cout << "ATK +" << 5 << " | DEF +" << 5 << " | HP max +" << 10 << endl;
                cout << "HP restaures : " << hp << "/" << hpMax << "\n" << endl;
            }
        }

        int getLevel()
        {
            return level;
        }
        int getXP()
        {
            return xp;
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
                cout << "Tu utilises " << item->getName()
                     << " : +" << item->getValue() << " HP. (HP : "
                     << hp << "/" << hpMax << ")" << endl;
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
            for (int i = 0; i < (int)inventory.size(); ++i)
            {
                cout << i << ". " << inventory[i]->getName()
                     << "  [" << inventory[i]->getType()
                     << " +" << inventory[i]->getValue() << " HP]"
                     << "  qty: " << inventory[i]->getQuantity() << endl;
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

        void addKill(string category)
        {
            monstersKilled++;
            totalVictories++;
            
            int xpGagne = 1;
            if (category == "BOSS")
            {
                xpGagne = 5;
            }
            else if (category == "NORMAL")
            {
                xpGagne = 2;
            }
            else if (category == "MINIBOSS")
            {
                xpGagne = 3;
            }
            
            gainXP(xpGagne);
        }

        void addSpare()
        {
            monstersSpared++;
            totalVictories++;
            gainXP(1);
        }
};