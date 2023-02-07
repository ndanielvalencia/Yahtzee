#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "message.h"
#include "functions.h"
using namespace sf;   
using namespace std;

// Default constructor. There's nothing to modify it with so it is empty

Message::Message(){
}

// Overloaded constructor. Necessary to initialize our class

Message::Message(string titleFont, string regularFont, double posX, double posY, int rollsLeft, double posX2, double posY2, int roundsLeft, double posX3, double posY3){

    if ((!_titleFont.loadFromFile(titleFont)) || (!_regularFont.loadFromFile(regularFont))){

        cout << "Could not load scoreboard fonts" << endl;
        throw;

    } 

    //Display the first line at the bottom of the screen 

    _mainMessage.setFont(_regularFont);
    _mainMessage.setCharacterSize(32);
    _mainMessage.setFillColor(Color::Black);
    _mainMessage.setPosition(Vector2f(posX, posY));
    _mainMessage.setString("Welcome to our game of yahtzee! press R to roll the dices.");

    //Changes the properties of the second line at the bottom of the screen

    _secondMessage.setFont(_regularFont);
    _secondMessage.setCharacterSize(32);
    _secondMessage.setFillColor(Color::Black);
    _secondMessage.setPosition(Vector2f(posX, posY + 30));

    // Displays the amount of dice rolls the user has left

    _rollsLeft.setFont(_regularFont);
    _rollsLeft.setCharacterSize(32);
    _rollsLeft.setFillColor(Color::White);
    _rollsLeft.setPosition(Vector2f(posX2, posY2));
    _rollsLeft.setString(charToString("Roll #") + to_string(rollsLeft));

    // Displays the amount of rounds the game has left

    _roundsLeft.setFont(_regularFont);
    _roundsLeft.setCharacterSize(32);
    _roundsLeft.setFillColor(Color::White);
    _roundsLeft.setPosition(Vector2f(posX3, posY3));
    _roundsLeft.setString(charToString("Rounds left: ") + to_string(roundsLeft));


    // Changes the properties of the letters indicators at the side of each category. The for loop will change the position of each letter automatically.

    for (unsigned int i = 0; i < 9; ++i){

        vector < Text > inputVector;

        for (unsigned int j = 0; j < 2; ++j){

        double xModifier = 0.0;
        double yModifier = 47.0;
        Text inputText;

        if (j == 0){

            xModifier = 35.0;

        } else if (j == 1){

            xModifier = 315.0;
        }

        inputText.setFont(_titleFont);
        inputText.setCharacterSize(32);
        inputText.setFillColor(Color::White);
        inputText.setPosition(Vector2f(posX2 + xModifier, posY2 + (yModifier * i) + 100.0));
        inputVector.push_back(inputText);
        }
    
    _letterIndicators.push_back(inputVector);
    }


}

// Changes the number of rolls left in the string

void Message::setRollsLeft(int rollsLeft){

    _rollsLeft.setString(charToString("Roll #") + to_string(rollsLeft));
}

// Changes the number of rounds left in the string

void Message::setRoundsLeft(int roundsLeft){

    _roundsLeft.setString(charToString("Rounds Left: ") + to_string(roundsLeft));
}

// Will show or hide the letter indicators for each category depending on the boolean parameter

void Message::displayLetterIndicators(bool trueOrFalse){

    if (trueOrFalse){

        _letterIndicators.at(0).at(0).setString("1");
        _letterIndicators.at(0).at(1).setString("7");
        _letterIndicators.at(1).at(0).setString("2");
        _letterIndicators.at(1).at(1).setString("8");
        _letterIndicators.at(2).at(0).setString("3");
        _letterIndicators.at(2).at(1).setString("9");
        _letterIndicators.at(3).at(0).setString("4");
        _letterIndicators.at(3).at(1).setString("J");
        _letterIndicators.at(4).at(0).setString("5");
        _letterIndicators.at(4).at(1).setString("Q");
        _letterIndicators.at(5).at(0).setString("6");
        _letterIndicators.at(5).at(1).setString("K");
        _letterIndicators.at(6).at(1).setString("A");

    } else{

        _letterIndicators.at(0).at(0).setString(" ");
        _letterIndicators.at(0).at(1).setString(" ");
        _letterIndicators.at(1).at(0).setString(" ");
        _letterIndicators.at(1).at(1).setString(" ");
        _letterIndicators.at(2).at(0).setString(" ");
        _letterIndicators.at(2).at(1).setString(" ");
        _letterIndicators.at(3).at(0).setString(" ");
        _letterIndicators.at(3).at(1).setString(" ");
        _letterIndicators.at(4).at(0).setString(" ");
        _letterIndicators.at(4).at(1).setString(" ");
        _letterIndicators.at(5).at(0).setString(" ");
        _letterIndicators.at(5).at(1).setString(" ");
        _letterIndicators.at(6).at(1).setString(" ");
    }

}

// This class inherits from the SFML DRAWABLE class. Allows the class to be drawn to the screen by using the window.draw function

void Message::draw(RenderTarget& target, RenderStates states) const{

    target.draw(_mainMessage);
    target.draw(_secondMessage);
    target.draw(_rollsLeft);
    target.draw(_roundsLeft);
    
    // Draws all of the letter indicators

    for (unsigned int i = 0; i < _letterIndicators.size(); ++i){

        for (unsigned int j = 0; j < _letterIndicators.at(i).size(); ++j){

            target.draw(_letterIndicators.at(i).at(j));
        }
    }
    

}

// Changes the main message displayed

void Message::setMainMessage(string message){

    _mainMessage.setString(message);
}

// Changes the second message displayed

void Message::setSecondMessage(string message){

    _secondMessage.setString(message);
}

// Deletes the second message

void Message::eraseSecondMessage(){

    _secondMessage.setString(" ");
}