#ifndef DICES_H
#define DICES_H

#include <string>
#include <SFML/Graphics.hpp>
#include "dice.h"
#include <vector>

using namespace sf;   
using namespace std;

// This class will represent 5 dices in a row. Simplifies the code and makes handling all of the dices at once a lot easier

class Dices{

    public:

        Dices();
        Dices(string filename, double posX, double posY);
        void draw(RenderWindow* window);
        Dice getDice(int position) const;
        void setDice(int position, int number);
        void rollDices();
        void setRollable(int position, bool yesOrNo);
        void setAllRollable(bool trueOrFalse);
        vector <int> getNumbers() const;
        bool getRollability(int position) const;
        void updateDisplay();
        void animateRoll(bool& startRolling);

    private:

        float _rollingDuration;
        vector <Dice> _dices;
        Texture _dicesTexture;
};

#endif