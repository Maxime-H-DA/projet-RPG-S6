#pragma once
#include <string>

using namespace std;

class ActAction
{
    private:
        string id;
        string text;
        int mercyImpact;

    public:
        ActAction() {}

        ActAction(string pId, string pText, int pImpact)
        {
            id = pId;
            text = pText;
            mercyImpact = pImpact;
        }

        string getId()
        {
            return id;
        }

        string getText()
        {
            return text;
        }

        int getImpact()
        {
            return mercyImpact;
        }
};