#ifndef GAME_EVENTS_H
#define GAME_EVENTS_H

#include <string>
#include <SFML/Graphics.hpp>
#include "dices.h"
#include "dices.h"
#include "message.h"
#include "scoreboard.h"

using namespace sf;   
using namespace std;

// Events called by our game

void gameOver(int& roundsLeft, Message& message, Scoreboard& scoreboard);
void startNewRound(int& rollsLeft, int& roundsLeft,Message& message,Dices& dices, Scoreboard& scoreboard);

#endif