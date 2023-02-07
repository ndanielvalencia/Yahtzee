#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "background.h"

using namespace sf;   
using namespace std;

//Default constructor. There's nothing to modify it with so it is empty

Background::Background(){
}

// Overloaded constructor. Sets the background image according to the filename passed as parameter

Background::Background(string filename){

    if (!_backgroundTexture.loadFromFile(filename)){
        cout << "Could not load background texture" << endl;
        throw;
    }
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite.setPosition(0,0);
}

// This class inherits from the SFML DRAWABLE class. Allows the window render to draw our background texture

void Background::draw(RenderTarget& target, RenderStates states) const{
    states.texture = _backgroundSprite.getTexture();
    target.draw(_backgroundSprite, states);
}