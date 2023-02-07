#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "scoreboard.h"
#include <algorithm>

using namespace sf;   
using namespace std;

//Global variables

const int NUM_VALS = 5;
const int NUM_CATEGORIES = 14;
const int UPPER_SECTION_BONUS_MIN = 63;


// Default constructor

Scoreboard::Scoreboard(){

    for (unsigned int i = 0; i < NUM_CATEGORIES; ++i) {

        _possibleScores.push_back(0);
    }
    for (int i = 0; i < NUM_CATEGORIES ; ++i) {

        _availableScoreCategories.push_back(false);
    }

    _sumUpperSection = 0;
    _totalScore = 0;

}

// Overloaded constructor. Uses a picture as the background for our scoreboard and fonts for titles/text

Scoreboard::Scoreboard(string filename, string titleFont, string regularFont, double posX, double posY){

    if (!_scoreboardTexture.loadFromFile(filename)){

        cout << "Could not load scoreboard texture" << endl;
        throw;
    }

    if ((!_titleFont.loadFromFile(titleFont)) || (!_regularFont.loadFromFile(regularFont))){

        cout << "Could not load scoreboard fonts" << endl;
        throw;

    } 

    _scoreboardSprite.setTexture(_scoreboardTexture);
    _scoreboardSprite.setPosition(Vector2f(posX, posY));

    for (unsigned int i = 0; i < 9; ++i){

        vector < Text > inputVector;

        for (unsigned int j = 0; j < 4; ++j){

        double xModifier = 0.0;
        double yModifier = 47.0;
        Text inputText;

        // Modifies the propeties of the categories text and automatically positions them in columns and rows using a vector of vectors

        if (j == 0){

            xModifier = 5.0;

        } else if (j == 1){

            xModifier = 165.0;

        } else if (j == 2){

            xModifier = 285.0;

        } else if (j == 3){

            xModifier = 445.0;
        }

        if (i == 0){

            inputText.setFont(_titleFont);

        } else {

            inputText.setFont(_regularFont);
        }
            
        inputText.setCharacterSize(32);
        inputText.setFillColor(Color::Black);
        inputText.setPosition(Vector2f(posX + xModifier, posY + (yModifier * i) + 10.0));
        inputVector.push_back(inputText);
        }
    
    _scoreboardTexts.push_back(inputVector);

    }

    _scoreboardTexts.at(0).at(0).setString("Upper Section");
    _scoreboardTexts.at(0).at(1).setString("Score");
    _scoreboardTexts.at(0).at(2).setString("Lower Section");
    _scoreboardTexts.at(0).at(3).setString("Score");
    _scoreboardTexts.at(1).at(0).setString("Ones");
    _scoreboardTexts.at(1).at(2).setString("Three of a Kind");
    _scoreboardTexts.at(2).at(0).setString("Twos");
    _scoreboardTexts.at(2).at(2).setString("Four of a Kind");
    _scoreboardTexts.at(3).at(0).setString("Threes");
    _scoreboardTexts.at(3).at(2).setString("Full House");
    _scoreboardTexts.at(4).at(0).setString("Fours");
    _scoreboardTexts.at(4).at(2).setString("Small Straight");
    _scoreboardTexts.at(5).at(0).setString("Fives");
    _scoreboardTexts.at(5).at(2).setString("Large Straight");
    _scoreboardTexts.at(6).at(0).setString("Sixes");
    _scoreboardTexts.at(6).at(2).setString("Chance");
    _scoreboardTexts.at(7).at(0).setString("Sum");
    _scoreboardTexts.at(7).at(2).setString("YAHTZEE");
    _scoreboardTexts.at(8).at(0).setString("Bonus");
    _scoreboardTexts.at(8).at(2).setString("TOTAL SCORE");

    // For loop used to shorten our code by setting a bunch of different strings as 0

    for (unsigned int i = 1; i < _scoreboardTexts.size(); ++i){

        _scoreboardTexts.at(i).at(1).setString(charToString("  ") + charToString("0"));
        _scoreboardTexts.at(i).at(3).setString(charToString("  ") + charToString("0"));
    }

    for (unsigned int i = 0; i < NUM_CATEGORIES; ++i) {

        _possibleScores.push_back(0);
    }
    for (int i = 0; i < NUM_CATEGORIES ; ++i) {

        _availableScoreCategories.push_back(false);
    }

    _sumUpperSection = 0;
    _totalScore = 0;
}

// Function that receives a vector that contains the dices numbers and returns a numeric score for the Aces category

int Scoreboard::calculateAces(const vector<int>& givenDiceValues) const {
    
    int isAces = 1;
    int numOfAces = 0;
    int valToSum = 0;


    for (unsigned int i = 0; i < givenDiceValues.size(); ++i) {

        if (givenDiceValues.at(i) == isAces) {

            ++numOfAces;
        }
    }

    if (numOfAces > 0) {

        for (unsigned int j = 0; j < givenDiceValues.size(); ++j) {

            if (givenDiceValues.at(j) == 1) {

                valToSum = valToSum + givenDiceValues.at(j);
            }
        }

    } 

    return valToSum;
}

// Function that returns true if the category Aces is available for scoring and automatically changes the text displayed to red to represent that the user is keeping that score for the remainder of the game
// Also updates the upper section bonus sum and total sum of the game

bool Scoreboard::scoreAces(const vector<int>& givenDiceValues){

    if (_availableScoreCategories.at(0) != true){

        int input = calculateAces(givenDiceValues);
        _availableScoreCategories.at(0) = true;
        _possibleScores.at(0) = input;
        _sumUpperSection += input;
        _totalScore += input;

        if (_sumUpperSection >= 63){

            _possibleScores.at(6) = 35;
            _scoreboardTexts.at(7).at(0).setFillColor(Color::Red);
            _scoreboardTexts.at(7).at(1).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(0).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(1).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(1).setString(charToString("  ") + to_string(_possibleScores.at(6)));
        }

        _scoreboardTexts.at(1).at(0).setFillColor(Color::Red);
        _scoreboardTexts.at(1).at(1).setFillColor(Color::Red);
        _scoreboardTexts.at(7).at(1).setString(charToString("  ") + to_string(_sumUpperSection));
        _scoreboardTexts.at(8).at(3).setString(charToString("  ") + to_string(_totalScore));
        return true;
    }

    else{

        return false;
    }
}

// Function that receives a vector that contains the dices numbers and returns a numeric score for the Twos category

int Scoreboard::calculateTwos(const  vector<int>& givenDiceValues ) const{

    int isTwos = 2;
    int numOfTwos = 0;
    int valToSum = 0;

    for (unsigned int i = 0; i < givenDiceValues.size(); ++i) {

        if (givenDiceValues.at(i) == isTwos) {

            ++numOfTwos;
        }
    }

    if (numOfTwos > 0) {

        for (unsigned int j = 0; j < givenDiceValues.size(); ++j) {

            if (givenDiceValues.at(j) == 2) {

                valToSum = valToSum + givenDiceValues.at(j);
            }
        }
    }

    return valToSum;
}

// Function that returns true if the category Twos is available for scoring and automatically changes the text displayed to red to represent that the user is keeping that score for the remainder of the game
// Also updates the upper section bonus sum and total sum of the game

bool Scoreboard::scoreTwos(const vector<int>& givenDiceValues){

    if (_availableScoreCategories.at(1) != true){
        int input = calculateTwos(givenDiceValues);
        _availableScoreCategories.at(1) = true;
        _possibleScores.at(1) = input;
        _sumUpperSection += input;
        _totalScore += input;

        if (_sumUpperSection >= 63){
            _possibleScores.at(6) = 35;
            _scoreboardTexts.at(7).at(0).setFillColor(Color::Red);
            _scoreboardTexts.at(7).at(1).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(0).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(1).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(1).setString(charToString("  ") + to_string(_possibleScores.at(6)));
        }
        _scoreboardTexts.at(2).at(0).setFillColor(Color::Red);
        _scoreboardTexts.at(2).at(1).setFillColor(Color::Red);
        _scoreboardTexts.at(7).at(1).setString(charToString("  ") + to_string(_sumUpperSection));
        _scoreboardTexts.at(8).at(3).setString(charToString("  ") + to_string(_totalScore));
        return true;
    }

    else{

        return false;
    }
}

// Function that receives a vector that contains the dices numbers and returns a numeric score for the Threes category

int Scoreboard::calculateThrees(const vector<int> &givenDiceValues) const {

    int isThrees = 3;
    int numOfThrees = 0;
    int valToSum = 0;

    for (unsigned int i = 0; i < givenDiceValues.size(); ++i) {

        if (givenDiceValues.at(i) == isThrees) {
            ++numOfThrees;
        }
    }

    if (numOfThrees > 0) {
        
        for (unsigned int j = 0; j < givenDiceValues.size(); ++j) {

            if (givenDiceValues.at(j) == 3) {

                valToSum = valToSum + givenDiceValues.at(j);
            }
        }
    }

    return valToSum;
}

// Function that returns true if the category Threes is available for scoring and automatically changes the text displayed to red to represent that the user is keeping that score for the remainder of the game
// Also updates the upper section bonus sum and total sum of the game

bool Scoreboard::scoreThrees(const vector<int>& givenDiceValues){

    if (_availableScoreCategories.at(2) != true){

        int input = calculateThrees(givenDiceValues);
        _availableScoreCategories.at(2) = true;
        _possibleScores.at(2) = input;
        _sumUpperSection += input;
        _totalScore += input;

        if (_sumUpperSection >= 63){
            _possibleScores.at(6) = 35;
            _scoreboardTexts.at(7).at(0).setFillColor(Color::Red);
            _scoreboardTexts.at(7).at(1).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(0).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(1).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(1).setString(charToString("  ") + to_string(_possibleScores.at(6)));
        }
        _scoreboardTexts.at(3).at(0).setFillColor(Color::Red);
        _scoreboardTexts.at(3).at(1).setFillColor(Color::Red);
        _scoreboardTexts.at(7).at(1).setString(charToString("  ") + to_string(_sumUpperSection));
        _scoreboardTexts.at(8).at(3).setString(charToString("  ") + to_string(_totalScore));
        return true;
    }

    else{

        return false;
    }
}

// Function that receives a vector that contains the dices numbers and returns a numeric score for the Fours category

int Scoreboard::calculateFours(const vector<int> &givenDiceValues) const {

    int isFour = 4;
    int numOfFours = 0;
    int valToSum = 0;

    for (unsigned int i = 0; i < givenDiceValues.size(); ++i) {

        if (givenDiceValues.at(i) == isFour) {

            ++numOfFours;
        }
    }

    if (numOfFours > 0) {

        for (unsigned int j = 0; j < givenDiceValues.size(); ++j) {

            if (givenDiceValues.at(j) == 4) {

                valToSum = valToSum + givenDiceValues.at(j);
            }
        }
    }

    return valToSum;
}

// Function that returns true if the category Fours is available for scoring and automatically changes the text displayed to red to represent that the user is keeping that score for the remainder of the game
// Also updates the upper section bonus sum and total sum of the game

bool Scoreboard::scoreFours(const vector<int>& givenDiceValues){

    if (_availableScoreCategories.at(3) != true){

        int input = calculateFours(givenDiceValues);
        _availableScoreCategories.at(3) = true;
        _possibleScores.at(3) = input;
        _sumUpperSection += input;
        _totalScore += input;

        if (_sumUpperSection >= 63){
            _possibleScores.at(6) = 35;
            _scoreboardTexts.at(7).at(0).setFillColor(Color::Red);
            _scoreboardTexts.at(7).at(1).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(0).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(1).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(1).setString(charToString("  ") + to_string(_possibleScores.at(6)));
        }
        _scoreboardTexts.at(4).at(0).setFillColor(Color::Red);
        _scoreboardTexts.at(4).at(1).setFillColor(Color::Red);
        _scoreboardTexts.at(7).at(1).setString(charToString("  ") + to_string(_sumUpperSection));
        _scoreboardTexts.at(8).at(3).setString(charToString("  ") + to_string(_totalScore));
        return true;
    }

    else{

        return false;
    }
}

// Function that receives a vector that contains the dices numbers and returns a numeric score for the Gives category

int Scoreboard::calculateFives(const vector<int> &givenDiceValues) const{

    int isFives = 5;
    int numOfFives = 0;
    int valToSum = 0;

    for (unsigned int i= 0; i < givenDiceValues.size(); ++i) {

        if (givenDiceValues.at(i) == isFives) {

            ++numOfFives;
        }
    }

    if (numOfFives > 0) {

        for (unsigned int j = 0; j < givenDiceValues.size(); ++j) {

            if (givenDiceValues.at(j) == 5) {

                valToSum = valToSum + givenDiceValues.at(j);
            }
        }
    }
    return valToSum;
}

// Function that returns true if the category Fives is available for scoring and automatically changes the text displayed to red to represent that the user is keeping that score for the remainder of the game
// Also updates the upper section bonus sum and total sum of the game

bool Scoreboard::scoreFives(const vector<int>& givenDiceValues){

    if (_availableScoreCategories.at(4) != true){

        int input = calculateFives(givenDiceValues);
        _availableScoreCategories.at(4) = true;
        _possibleScores.at(4) = input;
        _sumUpperSection += input;
        _totalScore += input;

        if (_sumUpperSection >= 63){
            _possibleScores.at(6) = 35;
            _scoreboardTexts.at(7).at(0).setFillColor(Color::Red);
            _scoreboardTexts.at(7).at(1).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(0).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(1).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(1).setString(charToString("  ") + to_string(_possibleScores.at(6)));
        }
        _scoreboardTexts.at(5).at(0).setFillColor(Color::Red);
        _scoreboardTexts.at(5).at(1).setFillColor(Color::Red);
        _scoreboardTexts.at(7).at(1).setString(charToString("  ") + to_string(_sumUpperSection));
        _scoreboardTexts.at(8).at(3).setString(charToString("  ") + to_string(_totalScore));
        return true;
    }

    else{

        return false;
    }
}

// Function that receives a vector that contains the dices numbers and returns a numeric score for the Sixes category

int Scoreboard::calculateSixes(const vector<int> &givenDiceValues) const{

    int isSixes = 6;
    int numOfSixes = 0;
    int valToSum = 0;

    for (unsigned int i = 0; i < givenDiceValues.size(); ++i) {

        if (givenDiceValues.at(i) == isSixes) {

            ++numOfSixes;
        }
    }

    if (numOfSixes > 0) {

        for (unsigned int j = 0; j < givenDiceValues.size(); ++j) {

            if (givenDiceValues.at(j) == 6) {

                valToSum = valToSum + givenDiceValues.at(j);
            }
        }
    }

    return valToSum;
}

// Function that returns true if the category Sixes is available for scoring and automatically changes the text displayed to red to represent that the user is keeping that score for the remainder of the game
// Also updates the upper section bonus sum and total sum of the game

bool Scoreboard::scoreSixes(const vector<int>& givenDiceValues){

    if (_availableScoreCategories.at(5) != true){

        int input = calculateSixes(givenDiceValues);
        _availableScoreCategories.at(5) = true;
        _possibleScores.at(5) = input;
        _sumUpperSection += input;
        _totalScore += input;

        if (_sumUpperSection >= 63){
            _possibleScores.at(6) = 35;
            _scoreboardTexts.at(7).at(0).setFillColor(Color::Red);
            _scoreboardTexts.at(7).at(1).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(0).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(1).setFillColor(Color::Red);
            _scoreboardTexts.at(8).at(1).setString(charToString("  ") + to_string(_possibleScores.at(6)));
        }

        _scoreboardTexts.at(6).at(0).setFillColor(Color::Red);
        _scoreboardTexts.at(6).at(1).setFillColor(Color::Red);
        _scoreboardTexts.at(7).at(1).setString(charToString("  ") + to_string(_sumUpperSection));
        _scoreboardTexts.at(8).at(3).setString(charToString("  ") + to_string(_totalScore));
        return true;

    } else{

        return false;
    }
}

// Function that receives a vector that contains the dices numbers and returns a numeric score for the Three of a Kind category

int Scoreboard::calculateThreeKind(const vector<int>& givenDiceValues) const {
    
    vector<int> dieVals = givenDiceValues; // User values
    sort(dieVals.begin(), dieVals.end());

    int equalElements = 0;
    int sumValues = 0;

    for (unsigned i = 0; i < 3 ; ++i) {

        if ((dieVals.at(i) == dieVals.at(i+1)) && (dieVals.at(i+1) == dieVals.at(i+2))) {

            equalElements = 3;

        } else {
            
            continue;
        }
    }

    if (equalElements == 3) {

        for (int i = 0; i < dieVals.size(); ++i) {

            sumValues += dieVals.at(i);
        }

    } 
    return sumValues;
}

// Function that returns true if the category Three of a Kind is available for scoring and automatically changes the text displayed to red to represent that the user is keeping that score for the remainder of the game
// Also updates the upper section bonus sum and total sum of the game

bool Scoreboard::scoreThreeKind(const vector<int>& givenDiceValues){

    if (_availableScoreCategories.at(7) != true){

        int input = calculateThreeKind(givenDiceValues);

        _availableScoreCategories.at(7) = true;
        _possibleScores.at(7) = input;
        _totalScore += input;
        _scoreboardTexts.at(1).at(2).setFillColor(Color::Red);
        _scoreboardTexts.at(1).at(3).setFillColor(Color::Red);
        _scoreboardTexts.at(8).at(3).setString(charToString("  ") + to_string(_totalScore));
        return true;

    } else{

        return false;
    }
}

// Function that receives a vector that contains the dices numbers and returns a numeric score for the Four of a Kind category

int Scoreboard::calculateFourKind(const vector<int>& givenDiceValues) const{

    vector<int> dieVals = givenDiceValues; // User values
    sort(dieVals.begin(), dieVals.end());

    int equalScoreBoards = 0;
    int sumValues = 0;

    for (unsigned int i = 0; i < 2; ++i) {

        if ((dieVals.at(i) == dieVals.at(i + 1)) && (dieVals.at(i + 1) == dieVals.at(i + 2)) && (dieVals.at(i + 2) == dieVals.at(i + 3))) {

            equalScoreBoards = 4;

        } else {

            continue;
        }
    }

    if (equalScoreBoards == 4) {

        for (unsigned int i = 0; i < dieVals.size(); ++i) {

            sumValues += dieVals.at(i);
        }
    }

    return sumValues;
}

// Function that returns true if the category Four of a kind is available for scoring and automatically changes the text displayed to red to represent that the user is keeping that score for the remainder of the game
// Also updates the upper section bonus sum and total sum of the game

bool Scoreboard::scoreFourKind(const vector<int>& givenDiceValues){

    if (_availableScoreCategories.at(8) != true){

        int input = calculateFourKind(givenDiceValues);
        _availableScoreCategories.at(8) = true;
        _possibleScores.at(8) = input;
        _totalScore += input;
        _scoreboardTexts.at(2).at(2).setFillColor(Color::Red);
        _scoreboardTexts.at(2).at(3).setFillColor(Color::Red);
        _scoreboardTexts.at(8).at(3).setString(charToString("  ") + to_string(_totalScore));
        return true;

    } else{

        return false;
    }
}

// Function that receives a vector that contains the dices numbers and returns a numeric score for the Full house category

int Scoreboard::calculateFullHouse(const vector<int> &givenDiceValues) const{

    vector<int> dieVals = givenDiceValues; // User values
    sort(dieVals.begin(), dieVals.end());

    if ( ((dieVals.at(0) == dieVals.at(1)) && (dieVals.at(1) == dieVals.at(2))) && ((dieVals.at(2) != dieVals.at(3)) && dieVals.at(3) == dieVals.at(4)) ) {

        return 25;

    } else if ( ((dieVals.at(0) == dieVals.at(1)) && (dieVals.at(1) != dieVals.at(2))) && ((dieVals.at(2) == dieVals.at(3)) && (dieVals.at(3) == dieVals.at(4))) ) {

        return 25;
    }

    else {

        return 0;
    }
}

// Function that returns true if the category Full House is available for scoring and automatically changes the text displayed to red to represent that the user is keeping that score for the remainder of the game
// Also updates the upper section bonus sum and total sum of the game

bool Scoreboard::scoreFullHouse(const vector<int>& givenDiceValues){

    if (_availableScoreCategories.at(9) != true){

        int input = calculateFullHouse(givenDiceValues);
        _availableScoreCategories.at(9) = true;
        _possibleScores.at(9) = input;
        _totalScore += input;
        _scoreboardTexts.at(3).at(2).setFillColor(Color::Red);
        _scoreboardTexts.at(3).at(3).setFillColor(Color::Red);
        _scoreboardTexts.at(8).at(3).setString(charToString("  ") + to_string(_totalScore));
        return true;

    } else{

        return false;
    }
}

// Function that receives a vector that contains the dices numbers and returns a numeric score for the Small Straight category

int Scoreboard::calculateSmallStraight(const vector<int>& givenDiceValues) const {

    vector<int> dieVals = givenDiceValues; // User values
    sort(dieVals.begin(), dieVals.end());


    for (unsigned int i = 0; i < dieVals.size() ; ++i) {

        for (unsigned int j = i + 1; j < dieVals.size() ; ++j) {

            for (unsigned int k = j + 1; k < dieVals.size(); ++k) {
                
                for (unsigned int l = k + 1; l < dieVals.size() ; ++l) {

                    if ((dieVals.at(j) - dieVals.at(i) == 1) && (dieVals.at(k) - dieVals.at(j) == 1) && (dieVals.at(l) - dieVals.at(k) == 1)){

                        return 30;

                    } else {

                        continue;
                    }
                }
            }
        }
    }

    return 0;
}

// Function that returns true if the category Small straight is available for scoring and automatically changes the text displayed to red to represent that the user is keeping that score for the remainder of the game
// Also updates the upper section bonus sum and total sum of the game

bool Scoreboard::scoreSmallStraight(const vector<int>& givenDiceValues){

    if (_availableScoreCategories.at(10) != true){

        int input = calculateSmallStraight(givenDiceValues);
        _availableScoreCategories.at(10) = true;
        _possibleScores.at(10) = input;
        _totalScore += input;
        _scoreboardTexts.at(4).at(2).setFillColor(Color::Red);
        _scoreboardTexts.at(4).at(3).setFillColor(Color::Red);
        _scoreboardTexts.at(8).at(3).setString(charToString("  ") + to_string(_totalScore));
        return true;

    } else{

        return false;
    }
}

// Function that receives a vector that contains the dices numbers and returns a numeric score for the Large straight category

int Scoreboard::calculateLargeStraight(const vector<int>& givenDiceValues) const{

    vector<int> dieVals = givenDiceValues; // User values
    sort(dieVals.begin(), dieVals.end());

    if ((dieVals.at(1) - dieVals.at(0) == 1) && (dieVals.at(2) - dieVals.at(1) == 1) && (dieVals.at(3) - dieVals.at(2) == 1) && (dieVals.at(4) - dieVals.at(3) == 1)){

        return 40;

    } else {

        return 0;
    }
}

// Function that returns true if the category Large straight is available for scoring and automatically changes the text displayed to red to represent that the user is keeping that score for the remainder of the game
// Also updates the upper section bonus sum and total sum of the game

bool Scoreboard::scoreLargeStraight(const vector<int>& givenDiceValues){

    if (_availableScoreCategories.at(11) != true){

        int input = calculateLargeStraight(givenDiceValues);
        _availableScoreCategories.at(11) = true;
        _possibleScores.at(11) = input;
        _totalScore += input;
        _scoreboardTexts.at(5).at(2).setFillColor(Color::Red);
        _scoreboardTexts.at(5).at(3).setFillColor(Color::Red);
        _scoreboardTexts.at(8).at(3).setString(charToString("  ") + to_string(_totalScore));
        return true;

    } else{

        return false;
    }
}

// Function that receives a vector that contains the dices numbers and returns a numeric score for the Chance category

int Scoreboard::calculateChance(const vector<int> &givenDiceValues) const {

    int totalSum = 0;

    for (unsigned int i = 0; i < givenDiceValues.size(); ++i) {
        totalSum = totalSum + givenDiceValues.at(i);
    }

    return totalSum;
}

// Function that returns true if the category Chance is available for scoring and automatically changes the text displayed to red to represent that the user is keeping that score for the remainder of the game
// Also updates the upper section bonus sum and total sum of the game

bool Scoreboard::scoreChance(const vector<int>& givenDiceValues){

    if (_availableScoreCategories.at(12) != true){

        int input = calculateChance(givenDiceValues);
        _availableScoreCategories.at(12) = true;
        _possibleScores.at(12) = input;
        _totalScore += input;
        _scoreboardTexts.at(6).at(2).setFillColor(Color::Red);
        _scoreboardTexts.at(6).at(3).setFillColor(Color::Red);
        _scoreboardTexts.at(8).at(3).setString(charToString("  ") + to_string(_totalScore));
        return true;

    } else{

        return false;
    }
}

// Function that receives a vector that contains the dices numbers and returns a numeric score for the Yahtzee category

int Scoreboard::calculateYahtzee(const vector<int>& givenDiceValues) const {

    int score = 50;

    for (int i = 1; i < 5; ++i){

        if (givenDiceValues.at(i) != givenDiceValues.front()){
            score = 0;
        }
    }

    return score;
}

// Function that returns true if the category Yahtzee is available for scoring and automatically changes the text displayed to red to represent that the user is keeping that score for the remainder of the game
// Also updates the upper section bonus sum and total sum of the game

bool Scoreboard::scoreYahtzee(const vector<int>& givenDiceValues){

    if (_availableScoreCategories.at(13) != true){

        int input = calculateYahtzee(givenDiceValues);
        _availableScoreCategories.at(13) = true;
        _possibleScores.at(13) = input;
        _totalScore += input;
        _scoreboardTexts.at(7).at(2).setFillColor(Color::Red);
        _scoreboardTexts.at(7).at(3).setFillColor(Color::Red);
        _scoreboardTexts.at(8).at(3).setString(charToString("  ") + to_string(_totalScore));
        return true;

    } else{

        return false;
    }
}

// Dynamically updates each scoreboard category to reflect the amount of points the user will get for each category they haven't scored in yet. Otherwise leave them as is.

void Scoreboard::updateDisplay(const vector<int>& diceValues){


    if (_availableScoreCategories.at(0) != true) {

        _possibleScores.at(0) = calculateAces(diceValues);

    } if (_availableScoreCategories.at(1) != true) {

        _possibleScores.at(1) = calculateTwos(diceValues);

    } if (_availableScoreCategories.at(2) != true) {

        _possibleScores.at(2) = calculateThrees(diceValues);

    } if (_availableScoreCategories.at(3) != true) {

        _possibleScores.at(3) = calculateFours(diceValues);

    } if (_availableScoreCategories.at(4) != true) {

        _possibleScores.at(4) = calculateFives(diceValues);

    } if (_availableScoreCategories.at(5) != true) {

        _possibleScores.at(5) = calculateSixes(diceValues);

    } if (_availableScoreCategories.at(7) != true) {

        _possibleScores.at(7) = calculateThreeKind(diceValues);

    } if (_availableScoreCategories.at(8) != true) {

        _possibleScores.at(8) = calculateFourKind(diceValues);

    } if (_availableScoreCategories.at(9) != true) {

        _possibleScores.at(9) = calculateFullHouse(diceValues);

    } if (_availableScoreCategories.at(10) != true) {

        _possibleScores.at(10) = calculateSmallStraight(diceValues);

    } if (_availableScoreCategories.at(11) != true) {

        _possibleScores.at(11) = calculateLargeStraight(diceValues);

    } if (_availableScoreCategories.at(12) != true) {

        _possibleScores.at(12) = calculateChance(diceValues);

    } if (_availableScoreCategories.at(13) != true) {

        _possibleScores.at(13) = calculateYahtzee(diceValues);
    }

    _scoreboardTexts.at(1).at(1).setString(charToString("  ") + to_string(_possibleScores.at(0)));
    _scoreboardTexts.at(2).at(1).setString(charToString("  ") + to_string(_possibleScores.at(1)));
    _scoreboardTexts.at(3).at(1).setString(charToString("  ") + to_string(_possibleScores.at(2)));
    _scoreboardTexts.at(4).at(1).setString(charToString("  ") + to_string(_possibleScores.at(3)));
    _scoreboardTexts.at(5).at(1).setString(charToString("  ") + to_string(_possibleScores.at(4)));
    _scoreboardTexts.at(6).at(1).setString(charToString("  ") + to_string(_possibleScores.at(5)));
    _scoreboardTexts.at(1).at(3).setString(charToString("  ") + to_string(_possibleScores.at(7)));
    _scoreboardTexts.at(2).at(3).setString(charToString("  ") + to_string(_possibleScores.at(8)));
    _scoreboardTexts.at(3).at(3).setString(charToString("  ") + to_string(_possibleScores.at(9)));
    _scoreboardTexts.at(4).at(3).setString(charToString("  ") + to_string(_possibleScores.at(10)));
    _scoreboardTexts.at(5).at(3).setString(charToString("  ") + to_string(_possibleScores.at(11)));
    _scoreboardTexts.at(6).at(3).setString(charToString("  ") + to_string(_possibleScores.at(12)));
    _scoreboardTexts.at(7).at(3).setString(charToString("  ") + to_string(_possibleScores.at(13)));
}

// Function that returns the user's total score

int Scoreboard::getScore() const{
    
    return _totalScore;
}

// This class inherits from the SFML class Drawable. Allows the window render to draw the entire scoreboard

void Scoreboard::draw(RenderTarget& target, RenderStates states) const{

    target.draw(_scoreboardSprite, states);

    for (unsigned int i = 0; i < _scoreboardTexts.size(); ++i){

        for (unsigned int j = 0; j < _scoreboardTexts.at(i).size(); ++j){

            target.draw(_scoreboardTexts.at(i).at(j));
        }

    }
}
