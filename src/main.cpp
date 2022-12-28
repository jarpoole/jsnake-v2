

#include <iostream>
#include "Game.h"
#include <ncurses.h>
#include "Debug.h"

using namespace std;

int main(int argc, char** argv){


	// DO NOT PUT THIS IN Game
	// Must be called first
	initscr();

	Debug debug;
	Game game;
	game.Start();

	endwin();
	return(0);

}

