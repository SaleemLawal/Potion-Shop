/*****************************************
** File:    Proj2.cpp
** This file contains the driver file that calls the files made
***********************************************/

#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int main () {
	srand(time(NULL));
	Game newGame;
	newGame.StartGame();
	return 0;
}
