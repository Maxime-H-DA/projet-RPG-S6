#pragma once
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

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

        Entity(string pname, int phpmax, int php, int pat, int pde)
        {
            name = pname;
            hpMax = phpmax;
            hp = php;
            at = pat;
            de = pde;
        }

        void attack(Entity* target)
        {
            int damage = rand() % (target->getHPMax() + 1);
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
};