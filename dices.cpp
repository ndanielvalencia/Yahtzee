#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "functions.h"
#include "dice.h"
#include "dices.h"

using namespace sf;   
using namespace std;

// Default constructor. We need to initialize the private member rolling duration for compatibility purposes

Dices::Dices(){

    _rollingDuration = 0.0f;
}

// Overloaded constructor. Creates the texture used by our dices' sprites.

Dices::Dices(string filename, double posX, double posY){

    if (!_dicesTexture.loadFromFile(filename)){

        cout << "Could not load dices texture" << endl;
        throw;
    }

    for (unsigned int i = 0; i < 5; ++i){

        Dice dice(&_dicesTexture, (i * 64) + posX, posY);
        _dices.push_back(dice);
    }

    _rollingDuration = 0.0f;
}

// Draws all of our dices at once in the window. This function helps shorten our code

void Dices::draw(RenderWindow* window){

    for (unsigned int i = 0; i < _dices.size(); ++i){

        window->draw(_dices.at(i));
    }
}

// Returns the dice at the given position

Dice Dices::getDice(int position) const{

    return _dices.at(position);
}

// Function that will modify the number of the dice at the given position

void Dices::setDice(int position, int number){

    _dices.at(position).setNumber(number);
}

// Rolls all of the 5 dices at the same time

void Dices::rollDices(){

    for (unsigned int j = 0; j < _dices.size(); ++j){
    
        _dices.at(j).setNumber(randomRoll());
    }
 

}

// Changes the rollability of the dice at the given position

void Dices::setRollable(int position, bool trueOrFalse){

    _dices.at(position).setRollable(trueOrFalse);
}

// Changes the rollability of all of the dices at once

void Dices::setAllRollable(bool trueOrFalse){

    for (unsigned int i = 0; i < _dices.size(); ++i){

        _dices.at(i).setRollable(trueOrFalse);
    }
}

// Returns a vector of integers that contains the numbers of all of the dices.

vector<int> Dices::getNumbers() const{

    vector<int> output;

    for (unsigned int i = 0; i < _dices.size(); ++i){

        int input;
        input = _dices.at(i).getNumber();
        output.push_back(input);
    }

    return output;
}

// Returns the rollability of the dice at the given position

bool Dices::getRollability(int position) const{

    return _dices.at(position).getRollability();
}

// Update all of the dices graphics by calling the update display function on each one of them

void Dices::updateDisplay(){

    for (unsigned int i = 0; i < 5; ++i){
        _dices.at(i).updateDisplay();
    }
}

// Uses a boolean in the main game to determine if the dices should keep changing its graphics or not, giving them a rolling animation effect

void Dices::animateRoll(bool& startRolling){

    if (startRolling == true){

            if (_rollingDuration >= 30.0f){

                startRolling = false;
                _rollingDuration = 0.0f;
            }

            else {

                this->rollDices();
            }

            _rollingDuration += 1.0f;
        }

}