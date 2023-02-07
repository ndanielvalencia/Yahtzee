#ifndef DICE_H
#define DICE_H

#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;   
using namespace std;

// This class will represent each individual dice in our game.

class Dice : public Drawable{

    public:
        Dice();
        Dice(Texture* texture, double posX, double posY);
        Sprite getSprite() const;
        bool getRollability() const;
        int getNumber() const;
        void setNumber(int number);
        void updateDisplay();
        void setRollable(bool yesOrNo);

    private:

        int _number;
        Sprite _diceSprite;
        virtual void draw(RenderTarget& target, RenderStates states) const;
        bool _rollable;
};

#endif