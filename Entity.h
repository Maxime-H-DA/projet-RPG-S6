
#pragma once
#include <string>
#include <vector>

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

        Entity(string pname, int phpmax, int php, int pat, int pde)
        {
            name = pname;
            hpMax = phpmax;
            hp = php;
            at = pat;
            de = pde;
        }
        
        virtual void takeDamage(int amount)
        {
            hp -= (amount - de);
            if (hp < 0)
            {
                hp = 0;
            } 
        }

        bool islandAlive()
        {
            return hp > 0;
        }

        string getName()
        {
            return name;
        }
};