/* CSCI 261 Final Project - Yahtzee!
 *
 * Authors: Nelson Daniel Valencia (Section E) 
 *          Rodrigo Gill (Section E)
 * 
 * (Almost) Full-fledged game of Yahtzee.
 * 
 * CREDITS:
 * "Kenney.nl" for the dices sprites
 * "ShyFonts" for the atarian fonts used in the game*/
 
#include <cstdlib>                             
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "functions.h"
#include "background.h"
#include "dice.h"
#include "dices.h"
#include "scoreboard.h"
#include "message.h"
#include "game_events.h"
#include <SFML/Audio.hpp>

using namespace sf;   
using namespace std;

// Global constant variables

const int WIDTH = 640;
const int HEIGHT = 640;

int main() {

    // Main's variables

    int rollsLeft = 3;
    int roundsLeft = 13;
    bool startRolling = false; // This boolean will aid us in animating our dices when they are rolling
    bool focus = true; // Used to keep track of the window's focus

    // Objects

    Background background("board.png");
    Dices dices("diceWhite.png", 155, 500);
    dices.updateDisplay();
    Scoreboard scoreboard("scoreboard.png", "atarianBold.ttf", "atarian.ttf", 60, 50);
    Message message("atarianBold.ttf", "atarian.ttf", 10, 560, rollsLeft, 5, 5, roundsLeft, 340, 5);
    Music music;
    if (!music.openFromFile("battle_yahtzee.wav")) // If it can't find the music file, exit the program
        return -1;
    music.play();

    // Main window's settings.

    ContextSettings settings;
    settings.antialiasingLevel = 8; // Adds antialiasing to our window. Makes round objects look less jagged.
    RenderWindow window( VideoMode(WIDTH, HEIGHT), "Yahtzee!" ); 
    window.setFramerateLimit(60); // Keeps a framerate of 60 FPS

    // Seeds our random function. To keep it extra random, we add a throwaway rand() function

    srand(time(NULL));
    rand();

    while( window.isOpen() ) {

        //Refreshes the window per frame

        window.clear( Color(40, 150, 40)); 

        // Drawing sequence

        window.draw(background);
        window.draw(scoreboard);
        window.draw(message);
        dices.draw(&window);
        dices.animateRoll(startRolling);

        // display the window

        window.display();   

        if (rollsLeft == 3){ // At the start of each round, hides letter indicators and greys out all dices

            message.displayLetterIndicators(false);
            dices.setAllRollable(false);

        } else if (!startRolling){ // Updates the scoreboard predictive scores once the dices stop rolling

            scoreboard.updateDisplay(dices.getNumbers());
        }
                     
        Event event;
        
        while( window.pollEvent(event) ) { // ask the window if any events occurred

            // Checks if windows is focused or not. This way, the program won't receive inputs from the user if it is not focused

            if (event.type == Event::GainedFocus) {

                focus = true;

            } else if(event.type == Event::LostFocus) {

                focus = false;
            }  

            // Detects the user keypresses and acts accordingly as long as there are still game rounds left. Very self explanatory

            if(event.type == Event::KeyPressed && roundsLeft > 0){

                if (event.key.code == Keyboard::R && focus == true && startRolling == false && rollsLeft > 0){
                
                    message.displayLetterIndicators(true);
                    --rollsLeft;

                    if (rollsLeft == 2){

                        dices.setAllRollable(true);
                        
                        message.setMainMessage("Click/touch the dices to set them aside,");
                        message.setSecondMessage("Or score in a category by pressing its respective key.");

                    } 
                    
                    else if (rollsLeft == 0 && startRolling == false){

                    message.setMainMessage("No more rolls left!");
                    message.setSecondMessage("Score in a category by pressing its respective key.");

                    } 

                    startRolling = true;
                }

                if (focus == true && startRolling == false && rollsLeft != 3 && roundsLeft > 0){

                    if (event.key.code == Keyboard::Num1 || event.key.code == Keyboard::Numpad1){

                        if (scoreboard.scoreAces(dices.getNumbers())){

                            startNewRound(rollsLeft, roundsLeft, message, dices, scoreboard);

                        } else {

                            message.setMainMessage("You cannot score in this category!");
                            message.setSecondMessage("Score in another category by pressing its respective key.");
                        }

                    } else if (event.key.code == Keyboard::Num2 || event.key.code == Keyboard::Numpad2){

                        if (scoreboard.scoreTwos(dices.getNumbers())){

                            startNewRound(rollsLeft, roundsLeft, message, dices, scoreboard);

                        } else {

                            message.setMainMessage("You cannot score in this category!");
                            message.setSecondMessage("Score in another category by pressing its respective key.");
                        }

                    } else if (event.key.code == Keyboard::Num3 || event.key.code == Keyboard::Numpad3){

                        if (scoreboard.scoreThrees(dices.getNumbers())){

                            startNewRound(rollsLeft, roundsLeft, message, dices, scoreboard);

                        } else {

                            message.setMainMessage("You cannot score in this category!");
                            message.setSecondMessage("Score in another category by pressing its respective key.");
                        }

                    } else if (event.key.code == Keyboard::Num4 || event.key.code == Keyboard::Numpad4){

                        if (scoreboard.scoreFours(dices.getNumbers())){

                            startNewRound(rollsLeft, roundsLeft, message, dices, scoreboard);

                        } else {

                            message.setMainMessage("You cannot score in this category!");
                            message.setSecondMessage("Score in another category by pressing its respective key.");
                        }

                    } else if (event.key.code == Keyboard::Num5 || event.key.code == Keyboard::Numpad5){

                        if (scoreboard.scoreFives(dices.getNumbers())){

                            startNewRound(rollsLeft, roundsLeft, message, dices, scoreboard);

                        } else {

                            message.setMainMessage("You cannot score in this category!");
                            message.setSecondMessage("Score in another category by pressing its respective key.");
                        }
                    } else if (event.key.code == Keyboard::Num6 || event.key.code == Keyboard::Numpad6){

                        if (scoreboard.scoreSixes(dices.getNumbers())){

                            startNewRound(rollsLeft, roundsLeft, message, dices, scoreboard);

                        } else {

                            message.setMainMessage("You cannot score in this category!");
                            message.setSecondMessage("Score in another category by pressing its respective key.");
                        }
                    } else if (event.key.code == Keyboard::Num7 || event.key.code == Keyboard::Numpad7){

                        if (scoreboard.scoreThreeKind(dices.getNumbers())){

                            startNewRound(rollsLeft, roundsLeft, message, dices, scoreboard);

                        } else {

                            message.setMainMessage("You cannot score in this category!");
                            message.setSecondMessage("Score in another category by pressing its respective key.");
                        }

                    } else if (event.key.code == Keyboard::Num8 || event.key.code == Keyboard::Numpad8){

                        if (scoreboard.scoreFourKind(dices.getNumbers())){

                            startNewRound(rollsLeft, roundsLeft, message, dices, scoreboard);

                        } else {

                            message.setMainMessage("You cannot score in this category!");
                            message.setSecondMessage("Score in another category by pressing its respective key.");
                        }

                    } else if (event.key.code == Keyboard::Num9 || event.key.code == Keyboard::Numpad9){

                        if (scoreboard.scoreFullHouse(dices.getNumbers())){

                            startNewRound(rollsLeft, roundsLeft, message, dices, scoreboard);

                        } else {

                            message.setMainMessage("You cannot score in this category!");
                            message.setSecondMessage("Score in another category by pressing its respective key.");
                        }

                    } else if (event.key.code == Keyboard::J){

                        if (scoreboard.scoreSmallStraight(dices.getNumbers())){

                            startNewRound(rollsLeft, roundsLeft, message, dices, scoreboard);

                        } else {

                            message.setMainMessage("You cannot score in this category!");
                            message.setSecondMessage("Score in another category by pressing its respective key.");
                        }

                    } else if (event.key.code == Keyboard::Q){

                        if (scoreboard.scoreLargeStraight(dices.getNumbers())){

                            startNewRound(rollsLeft, roundsLeft, message, dices, scoreboard);

                        } else {

                            message.setMainMessage("You cannot score in this category!");
                            message.setSecondMessage("Score in another category by pressing its respective key.");
                        }

                    } else if (event.key.code == Keyboard::K){

                        if (scoreboard.scoreChance(dices.getNumbers())){

                            startNewRound(rollsLeft, roundsLeft, message, dices, scoreboard);

                        } else {

                            message.setMainMessage("You cannot score in this category!");
                            message.setSecondMessage("Score in another category by pressing its respective key.");
                        }

                    } else if (event.key.code == Keyboard::A){

                        if (scoreboard.scoreYahtzee(dices.getNumbers())){

                            startNewRound(rollsLeft, roundsLeft, message, dices, scoreboard);

                        } else {

                            message.setMainMessage("You cannot score in this category!");
                            message.setSecondMessage("Score in another category by pressing its respective key.");
                        }
                    }
                }
            // Updates the amount of rolls and rounds left after every keypress

            message.setRollsLeft(rollsLeft);
            message.setRoundsLeft(roundsLeft);
            }
            
            // Detects mouse clicks and other conditions that need to be met to be able to hold a dice from rolling

            if (event.mouseButton.button == Mouse::Left && event.type == Event::MouseButtonReleased && focus == true && startRolling == false && rollsLeft != 3 && rollsLeft != 0 && roundsLeft > 0){
                
                // This for long checks that the mouse position at the time of the click is within the boundaries of a dice (in terms of the x and y axis) and proceeds to change its rollability

                for (unsigned int i = 0; i < 5; ++i){

                    if ((Mouse::getPosition(window).x >= dices.getDice(i).getSprite().getPosition().x) && (Mouse::getPosition(window).x <= dices.getDice(i).getSprite().getPosition().x + 64) && (Mouse::getPosition(window).y >= dices.getDice(i).getSprite().getPosition().y) && (Mouse::getPosition(window).y <= dices.getDice(i).getSprite().getPosition().y + 64)){

                        if (dices.getRollability(i) == true){

                            dices.setRollable(i, false);

                        } else {

                            dices.setRollable(i, true);
                        
                        }
                    }
                }
            }

            if( event.type == Event::Closed ) { // if event type is a closed event
                                                // i.e. they clicked the X on the window
                window.close();                 // then close our window
            }
        }
    }
    return EXIT_SUCCESS;
}
