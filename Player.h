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
        Player(string playerName) : Entity(playerName, 100, 30, 10)
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

        string getCategory() const override
        {
            return "PLAYER";
        }

        void attack(Entity* target) override
        {
            int base = getAt() - target->getDe();
            if (base < 1) base = 1;

            uniform_int_distribution<int> dist(base, base * 2.5);
            int damage = dist(rng);
            
            cout << getName() << " dechaine une attaque de " << damage << " degats !" << endl;
            target->takeDamage(damage);
        }

        void gainXP(int amount)
        {
            xp += amount;
            while (xp >= 5)
            {
                xp -= 5;
                level++;
                setAt(getAt() + 5);
                setDe(getDe() + 3);
                setHPMax(getHPMax() + 20);
                setHP(getHPMax());
                
                cout << "\n--- MONTEE DE NIVEAU : " << level << " ---" << endl;
            }
        }

        void useItem(int index)
        {
            if (index < 0 || index >= (int)inventory.size()) return;

            Item* item = inventory[index];
            int newHP = getHP() + item->getValue();
            if (newHP > getHPMax())
            {
                newHP = getHPMax();
            }
            setHP(newHP);
            
            cout << "Objet " << item->getName() << " utilise. HP: " << getHP() << endl;

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
                cout << "Rien dans les poches." << endl;
                return;
            }
            for (int i = 0; i < (int)inventory.size(); ++i)
            {
                cout << i << ". " << inventory[i]->getName() << " (x" << inventory[i]->getQuantity() << ")" << endl;
            }
        }

        void addKill(string cat)
        {
            monstersKilled++;
            totalVictories++;
            if (cat == "BOSS")
            {
                gainXP(5);
            }
            else if (cat == "MINIBOSS")
            {
                gainXP(3);
            }
            else
            {
                gainXP(2);
            }
        }

        void addSpare()
        {
            monstersSpared++;
            totalVictories++;
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
        int getLevel()
        {
            return level;
        }

        void setlevel(int lvl)
        {
            level = lvl;
        }

};