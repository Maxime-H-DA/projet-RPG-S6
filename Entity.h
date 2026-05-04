#pragma once
#include <string>
#include <iostream>
#include <random>

using namespace std;

static mt19937 rng(random_device{}());

class Entity
{
    private:
        string name;
        int hpMax;
        int hp;
        int at;
        int de;
 
    public:
        virtual ~Entity() {}

        virtual void attack(Entity* target) = 0;

        Entity(string pname, int phpmax, int pat, int pde)
        {
            name = pname;
            hpMax = phpmax;
            hp = phpmax;
            at = pat;
            de = pde;
        }

        void takeDamage(int damage)
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

        void setAt(int val)
        {
            at = val;
        }
        void setDe(int val)
        {
            de = val;
        }
        void setHPMax(int val)
        {
            hpMax = val;
            if (hp > hpMax)
            {
                hp = hpMax;
            }
        }
};