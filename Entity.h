#pragma once
#include <string>
#include <iostream>
#include <random>

using namespace std;

static mt19937 rng(random_device{}());

class Entity
{
    protected:
        string name;
        int hpMax;
        int hp;
        int at;
        int de;

    public:
        virtual ~Entity() {}

        virtual string getCategory() const = 0;

        Entity(string pname, int phpmax, int pat, int pde)
        {
            name = pname;
            hpMax = phpmax;
            hp = phpmax;
            at = pat;
            de = pde;
        }

        virtual void attack(Entity* target)
        {
            int base = at - target->getDe();
            if (base < 1)
            {
                base = 1;
            }
            uniform_int_distribution<int> dist(base / 100, base / 50);
            int damage = dist(rng);
            cout << name << " attaque pour " << damage << " degats !" << endl;
            target->takeDamage(damage);
        }

        virtual void takeDamage(int damage)
        {
            hp -= damage;
            if (hp < 0)
            {
                hp = 0;
            }
        }

        bool isAlive()
        {
            return hp > 0;
        }

        string getName()
        {
            return name;
        }
        int getHP()
        {
            return hp;
        }
        int getHPMax()
        {
            return hpMax;
        }
        int getAt()
        {
            return at;
        }
        int getDe() 
        { 
            return de; 
        }

        void setHP(int hpValue)
        {
            hp = hpValue;
            if (hp > hpMax)
            {
                hp = hpMax;
            }
        }
};