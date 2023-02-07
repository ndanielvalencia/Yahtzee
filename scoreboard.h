#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;   
using namespace std;
string charToString(const char * input);

// This class determines and keeps track of all of our game's scores, while also graphically displaying them.

class Scoreboard : public Drawable{

    public:

        Scoreboard();
        Scoreboard(string filename, string titleFont, string regularFont, double posX, double posY);
        int calculateAces(const vector<int>& givenDiceValues) const;
        bool scoreAces(const vector<int>& givenDiceValues);
        int calculateTwos(const  vector<int>& givenDiceValues) const;
        bool scoreTwos(const vector<int>& givenDiceValues);
        int calculateThrees(const  vector<int>& givenDiceValues) const;
        bool scoreThrees(const vector<int>& givenDiceValues);
        int calculateFours(const  vector<int>& givenDiceValues) const;
        bool scoreFours(const vector<int>& givenDiceValues);
        int calculateFives(const vector<int> &givenDiceValues) const;
        bool scoreFives(const vector<int>& givenDiceValues);
        int calculateSixes(const  vector<int>& givenDiceValues ) const;
        bool scoreSixes(const vector<int>& givenDiceValues);
        int calculateThreeKind(const vector<int>& givenDiceValues) const;
        bool scoreThreeKind(const vector<int>& givenDiceValues);
        int calculateFourKind(const  vector<int>& givenDiceValues) const;
        bool scoreFourKind(const vector<int>& givenDiceValues);
        int calculateFullHouse(const vector<int> &givenDiceValues) const;
        bool scoreFullHouse(const vector<int>& givenDiceValues);
        int calculateSmallStraight(const  vector<int>& givenDiceValues) const;
        bool scoreSmallStraight(const vector<int>& givenDiceValues);
        int calculateLargeStraight(const  vector<int>& givenDiceValues) const;
        bool scoreLargeStraight(const vector<int>& givenDiceValues);
        int calculateYahtzee(const  vector<int>& givenDiceValues) const;
        bool scoreYahtzee(const vector<int>& givenDiceValues);
        int calculateChance(const  vector<int>& givenDiceValues) const;
        bool scoreChance(const vector<int>& givenDiceValues);
        int getScore() const;
        void updateDisplay(const vector<int>& diceValues);

    private:

        Texture _scoreboardTexture;
        Sprite _scoreboardSprite;
        Font _titleFont;
        Font _regularFont;
        vector < vector < Text > > _scoreboardTexts;
        vector <int> _possibleScores;
        vector <int> _availableScoreCategories;
        int _sumUpperSection;
        int _totalScore;
        virtual void draw(RenderTarget& target, RenderStates states) const;
};

#endif