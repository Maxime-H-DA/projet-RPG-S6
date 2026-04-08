#include <string>
#include <vector>

class Entity
{
protected:
    std::string name;
    int hpMax;
    int hp;
    int at;
    int de;

public:
    virtual void takeDamage(int amount)
    {
        hp -= (amount - de);
        if (hp < 0) hp = 0;
    }

    bool islandAlive()
    {
        return hp > 0;
    }
};