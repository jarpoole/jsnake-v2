

#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include <list>
#include "GameData.h"
#include "InputKeys.h"
#include "Display.h"

class Game {

	public:
		Game();
		~Game();
		

		void SplashScreen();
		void Start();
		void MainMenu();
		void Run();
		void DisplayScore();


	private:
		std::string toString(int number);		
		
		GameData gameData;
		Display gameBoard;
		InputKeys snakeKeys;
};

#endif
