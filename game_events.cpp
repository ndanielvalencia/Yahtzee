#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "functions.h"
#include "dice.h"
#include "dices.h"
#include "message.h"
#include "scoreboard.h"
#include "game_events.h"
using namespace sf;   
using namespace std;

// Ends the game. Checks if the user has a previous stored score file. If yes, the function checks it against the current score and displays the higher one on the screen. If not, displays the current score.

void gameOver(int& roundsLeft, Message& message, Scoreboard& scoreboard){

    // Compare scores //
    
    ifstream userScoreRecord("score_record.txt");
    int currentUserScore = scoreboard.getScore();
    int userOldHighScore = 0;

    if (!userScoreRecord.is_open()) { // Set a new high score if it is the first trial (create a new file)
        
        ofstream userFirstScore("score_record.txt");

        if (!userFirstScore.is_open()) {

            cerr << "Could not save user new score." << endl;
            throw;
        }

        userFirstScore << currentUserScore << endl;
        userFirstScore.close();
    } else {
    // If is not the first trial, compared new score with old score (read a previous file) 

    userScoreRecord >> userOldHighScore;
    userScoreRecord.close();
    }

    // If current score is higher, let user know they got a new high score//

    if ( currentUserScore > userOldHighScore ) {

        ofstream userNewHighScore("score_record.txt");
        if (!userNewHighScore.is_open()) {

            cerr << "Could not save user new score." << endl;
            throw;
        }

        message.setMainMessage("Game is over!");
        message.setSecondMessage("You got a new high score! your score is " + to_string(currentUserScore));
        userNewHighScore << currentUserScore << endl;
    }
        // If new score is better, put this score as the new best //

    else {

        
        message.setMainMessage("Game is over!");
        message.setSecondMessage("Your current high score is  " + to_string(userOldHighScore));
    }
}

// Starts a new round of Yahtzee using the main game's variables and classes.

void startNewRound(int& rollsLeft, int& roundsLeft,Message& message,Dices& dices, Scoreboard& scoreboard){

    rollsLeft = 3;
    --roundsLeft;
    message.displayLetterIndicators(false);

    if (roundsLeft <= 0){

        gameOver(roundsLeft, message, scoreboard);

    } else{

        dices.setAllRollable(true);
        message.setMainMessage("Press R to roll the dices again!");
        message.eraseSecondMessage();
    }
}
