#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "functions.h"
using namespace sf;   
using namespace std;

// Function that converts a const char datatype to a string

string charToString(const char * input){

    string output(input);
    return output;
}

// Function that returns a random number between 1 and 6

int randomRoll(){

    return rand() % 6 + 1;
}

