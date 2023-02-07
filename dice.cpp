#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "dice.h"

using namespace sf;   
using namespace std;

// Default constructor. We need to initialize these variables, otherwise some functions within other classes will not work properly

Dice::Dice(){

    _rollable = false;
    _number = 1;
}

// Overloaded constructor. Sets our dice's texture and sprite.

Dice::Dice(Texture* texture, double posX, double posY){ // Our texture needs to be passed as a pointer. For efficiency purposes, as we only need to store one texture in our dices class and initialize each individual dice sprite with it.

    _diceSprite.setTexture(*texture); 
    _diceSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    _diceSprite.setPosition(Vector2f(posX, posY));
    _rollable = false;
    _number = 1;
}

// Returns each dice's sprite

Sprite Dice::getSprite() const{

    return _diceSprite;
}

// Check whether the dice is rollable at any given point in the game

bool Dice::getRollability() const{

    return _rollable;
}

// Returns our current dice's number

int Dice::getNumber() const{

    return _number;
}

// Changes our current dice's number

void Dice::setNumber(int number){

    if (_rollable == true){

        _number = number;

    } 

    updateDisplay();

}

// This class inherits from the SFML class Drawable. Allows the window render to draw each dice sprite

void Dice::draw(RenderTarget& target, RenderStates states) const{

    states.texture = _diceSprite.getTexture();
    target.draw(_diceSprite, states);
}

// Updates the dice graphics depending on its properties

void Dice::updateDisplay(){

    int modifier = 0;

    if (_rollable == false){

        modifier = 192;
    }

    switch (_number){

        case 1:
            _diceSprite.setTextureRect(sf::IntRect(modifier + 0, 0, 64, 64));
            break;
        case 2:
            _diceSprite.setTextureRect(sf::IntRect(modifier + 64, 0, 64, 64));
            break;
        case 3:
            _diceSprite.setTextureRect(sf::IntRect(modifier + 128, 0, 64, 64));
            break;
        case 4:
            _diceSprite.setTextureRect(sf::IntRect(modifier + 0, 64, 64, 64));
            break;
        case 5:
            _diceSprite.setTextureRect(sf::IntRect(modifier + 64, 64, 64, 64));
            break;
        case 6:
            _diceSprite.setTextureRect(sf::IntRect(modifier + 128, 64, 64, 64));
            break;
    }   
}

// Changes the dice's rollability

void Dice::setRollable(bool trueOrFalse){

    if (trueOrFalse){

        _rollable = true;

    } else {

        _rollable = false;
    }

    updateDisplay();
}


