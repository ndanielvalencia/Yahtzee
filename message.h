#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;   
using namespace std;

// This class will display all the necessary info (Rounds left, rolls left, keys to press, etc) for the game to function properly

class Message: public Drawable{

    public:

        Message();
        Message(string titleFont, string regularFont, double posX, double posY, int rollsLeft, double posX2, double posY2, int roundsLeft, double posX3, double posY3);
        void setRollsLeft(int rollsLeft);
        void setRoundsLeft(int roundsLeft);
        void displayLetterIndicators(bool trueOrFalse);
        void setMainMessage(string message);
        void setSecondMessage(string message);
        void eraseSecondMessage();

    private:
    
        Font _regularFont;
        Font _titleFont;
        Text _mainMessage;
        Text _secondMessage;
        Text _rollsLeft;
        Text _roundsLeft;
        vector < vector < Text > > _letterIndicators;
        virtual void draw(RenderTarget& target, RenderStates states) const;
};

#endif