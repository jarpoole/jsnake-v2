
#include <sstream>
#include <string>
#include <iostream>
#include <list>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "Display.h"
#include "InputKeys.h"
#include "Snake.h"
#include "Random.h"
#include "GameData.h"
#include "Game.h"

#include "Menu.h"
#include "MenuPanel.h"
#include "MenuItem.h"

#include "Debug.h"

#include "Constants.h"

using namespace std;


Game::Game(){

	timeout(0);
	noecho();  
	keypad(stdscr, TRUE);

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	
	//Snake Colors
	init_pair(2, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_BLACK, COLOR_CYAN);
	init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(5, COLOR_BLACK, COLOR_GREEN);
	init_pair(6, COLOR_BLACK, COLOR_YELLOW);
	
	//Menu Color

	init_pair(10, COLOR_BLACK, COLOR_GREEN);
	
	// This should be in Random.cpp with Static
	srand(time(NULL));

}

Game::~Game(){
}

std::string Game::toString(int number){

	std::ostringstream stream;
	stream << number;
	return stream.str();

}



void Game::Start(){

	SplashScreen();
	MainMenu();

	while(gameData.GetPlay() == true){

		Run();
		DisplayScore();

		if(gameData.GetExit() == true){
			break;
		}
	} 

	gameBoard.ClearScreen();
	return;
}

void Game::SplashScreen(){
	
	Display splashScreen;

	splashScreen.LoadLevel(0);
	splashScreen.Paint();
	usleep(3000000);

}


void Game::MainMenu(){

	snakeKeys.SetTimeout(0);
	
	Menu menu(&gameData);

	MenuPanel mainPanel("Main Menu");
	MenuPanel humanPanel("Number Human Players");
	MenuPanel aiPanel("Number AI Players");
	MenuPanel gamespeedPanel("Gamespeed");
	MenuPanel levelPanel("Level");
	MenuPanel wrapPanel("Wrapping");

	// Main Panel Items
	GameData::FunctionPointerBool setPlay = &GameData::SetPlay;
	GameData::FunctionPointerBool setExit = &GameData::SetExit;
	MenuItem humanItem("Number of Human Players", 0, &humanPanel, NULL);
	MenuItem aiItem("Number of AI Players", 0, &aiPanel, NULL);
	MenuItem gamespeedItem("Set Gamespeed", 0,&gamespeedPanel, NULL); 
	MenuItem levelItem("Select a Level", 0,&levelPanel, NULL); 
	MenuItem wrapItem("Wrapping", 0, &wrapPanel, NULL); 
	MenuItem playItem("Play", true, NULL, NULL, &gameData, setPlay);
	MenuItem exitItem("Exit", true, NULL, NULL, &gameData, setExit);

	mainPanel.AddItem(&humanItem);
	mainPanel.AddItem(&aiItem);
	mainPanel.AddItem(&gamespeedItem);
	mainPanel.AddItem(&levelItem);
	mainPanel.AddItem(&wrapItem);
	mainPanel.AddItem(&playItem);
	mainPanel.AddItem(&exitItem);


	//Human Players
	GameData::FunctionPointerInt setHumanNumber = &GameData::SetHumanNumber;
	
	MenuItem human0("0", 0, NULL, &mainPanel, &gameData, setHumanNumber);
	MenuItem human1("1", 1, NULL, &mainPanel, &gameData, setHumanNumber);
	MenuItem human2("2", 2, NULL, &mainPanel, &gameData, setHumanNumber);
	MenuItem human3("3", 3, NULL, &mainPanel, &gameData, setHumanNumber);
	MenuItem human4("4", 4, NULL, &mainPanel, &gameData, setHumanNumber);
	
	humanPanel.AddItem(&human0);
	humanPanel.AddItem(&human1);
	humanPanel.AddItem(&human2);
	humanPanel.AddItem(&human3);
	humanPanel.AddItem(&human4);
	
	//AI Players
	GameData::FunctionPointerInt setAINumber = &GameData::SetAINumber;
	
	MenuItem ai0("0", 0, NULL, &mainPanel, &gameData, setAINumber);
	MenuItem ai1("1", 1, NULL, &mainPanel, &gameData, setAINumber);
	MenuItem ai2("2", 2, NULL, &mainPanel, &gameData, setAINumber);
	MenuItem ai3("3", 3, NULL, &mainPanel, &gameData, setAINumber);
	MenuItem ai4("4", 4, NULL, &mainPanel, &gameData, setAINumber);
	MenuItem ai5("5", 5, NULL, &mainPanel, &gameData, setAINumber);
	MenuItem ai6("6", 6, NULL, &mainPanel, &gameData, setAINumber);
	MenuItem ai7("7", 7, NULL, &mainPanel, &gameData, setAINumber);
	MenuItem ai8("8", 8, NULL, &mainPanel, &gameData, setAINumber);
	MenuItem ai9("9", 9, NULL, &mainPanel, &gameData, setAINumber);
	MenuItem ai10("10", 10, NULL, &mainPanel, &gameData, setAINumber);
	
	aiPanel.AddItem(&ai0);
	aiPanel.AddItem(&ai1);
	aiPanel.AddItem(&ai2);
	aiPanel.AddItem(&ai3);
	aiPanel.AddItem(&ai4);
	aiPanel.AddItem(&ai5);
	aiPanel.AddItem(&ai6);
	aiPanel.AddItem(&ai7);
	aiPanel.AddItem(&ai8);
	aiPanel.AddItem(&ai9);
	aiPanel.AddItem(&ai10);
	
	// Gamespeed Panel	
	GameData::FunctionPointerInt setSpeed = &GameData::SetGameSpeed;
	
	MenuItem value0("Slow", 100000, NULL, &mainPanel, &gameData, setSpeed);
	MenuItem value1("Normal", 50000, NULL, &mainPanel, &gameData, setSpeed);
	MenuItem value2("Fast", 25000, NULL, &mainPanel, &gameData, setSpeed);
	MenuItem value3("Ultra", 15000, NULL, &mainPanel, &gameData, setSpeed);

	gamespeedPanel.AddItem(&value0);
	gamespeedPanel.AddItem(&value1);
	gamespeedPanel.AddItem(&value2);
	gamespeedPanel.AddItem(&value3);

	// Level select Panel
	GameData::FunctionPointerInt setLevel = &GameData::SetLevel;
	
	MenuItem level1("Empty Field", 1, NULL, &mainPanel, &gameData, setLevel);
	MenuItem level2("Square Area", 2, NULL, &mainPanel, &gameData, setLevel);
	MenuItem level3("Helicopter Landing", 3, NULL, &mainPanel, &gameData, setLevel);
	MenuItem level4("Maze", 4, NULL, &mainPanel, &gameData, setLevel);
	MenuItem level5("Teleporter corner", 5, NULL, &mainPanel, &gameData, setLevel);

	levelPanel.AddItem(&level1);
	levelPanel.AddItem(&level2);
	levelPanel.AddItem(&level3);
	levelPanel.AddItem(&level4);
	levelPanel.AddItem(&level5);

	// Wrapping Panel
	GameData::FunctionPointerBool setWrap = &GameData::SetWrapping;
	
	MenuItem wrapOn("On", true, NULL, &mainPanel, &gameData, setWrap);
	MenuItem wrapOff("Off", false, NULL, &mainPanel, &gameData, setWrap);

	wrapPanel.AddItem(&wrapOn);
	wrapPanel.AddItem(&wrapOff);
	
	//Start the Menu
	menu.SetActivePanel(&mainPanel);
	menu.Refresh();

	// CleanUp
	menu.Clear();

}

void Game::Run(){


	gameData.SetPlay(false);

	//Load Level	
	gameBoard.ClearScreen();
	gameBoard.LoadLevel(gameData.GetLevel());
	gameBoard.Paint();
	

	if (gameData.GetWrapping() == false){
		//Override outer boarder on any level
		gameBoard.CreateBorder();
		gameBoard.Paint();
	}
	

	std::list<Snake> humanSnakes;
	std::list<Snake> aiSnakes;
	
	int humanNumber = gameData.GetHumanNumber();
	int aiNumber = gameData.GetAINumber();

	//Calculate number of starting rows and colunms
	Random rand;	
	int totalNumber = humanNumber;
	int row = 0;
	int col = 0;
	do{

		row++;
		col = (gameBoard.GetLastCol() * row) / (totalNumber + 1);  

	}while(col < 15);


	
	//Create all human players

	if (humanNumber > 0){
		Snake player1(false, ' ', 2, gameBoard.GetLastRow() / 2, col, 11, KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN);
		humanSnakes.insert(humanSnakes.end(), player1);
		gameData.AddScore(player1.GetId());		
	}

	if(humanNumber > 1){
		Snake player2(false, ' ', 3, gameBoard.GetLastRow() / 2, col * 2, 12, 'a', 'd', 'w', 's');
		humanSnakes.insert(humanSnakes.end(), player2);
		gameData.AddScore(player2.GetId());		
	}

	if(humanNumber > 2){
		Snake player3(false, ' ', 4, gameBoard.GetLastRow() / 2, col * 3, 13, 'j', 'l', 'i', 'k');
		humanSnakes.insert(humanSnakes.end(), player3);
		gameData.AddScore(player3.GetId());		
	}

	if(humanNumber > 3){
		Snake player4(false, ' ', 5, gameBoard.GetLastRow() / 2, col * 4, 14, 'f', 'h', 't', 'g');
		humanSnakes.insert(humanSnakes.end(), player4);
		gameData.AddScore(player4.GetId());		
	}

	char aiSnakeChar[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };	

	//Create all AI players

	for (int j = 0; j < aiNumber; j++){
		
		int startRow = 0;
		int startCol = 0;		
		gameBoard.GetRandomChar(' ', startRow, startCol);

		Snake ai(true, aiSnakeChar[j], 6, startRow, startCol, 20, -1, -1, -1, -1);
		aiSnakes.insert(aiSnakes.end(), ai);
		gameData.AddScore(ai.GetId());		

	}

	//Load input keys for all snakes
	for(std::list<Snake>::iterator it = humanSnakes.begin(); it != humanSnakes.end(); it++){
		snakeKeys.AddKey((*it).GetKeyLeft());
		snakeKeys.AddKey((*it).GetKeyRight());
		snakeKeys.AddKey((*it).GetKeyUp());
		snakeKeys.AddKey((*it).GetKeyDown());
	}
	


	int exit = 0;

	do{

		//Process keyboard inputs for all human snakes

		int moreInput = 1;
		while(moreInput){

			int inputKey = snakeKeys.GetInputKey();
			if(inputKey == -1){
				moreInput = 0;
			} else {
				for(std::list<Snake>::iterator it = humanSnakes.begin(); it != humanSnakes.end(); it++){
					(*it).ProcessInput(inputKey);
				}
			}
		}

		//Move all Player Snakes
		for(std::list<Snake>::iterator it = humanSnakes.begin(); it != humanSnakes.end(); it++){
			(*it).Move();
			if (gameData.GetWrapping() == true){
				(*it).CheckWrap(&gameBoard);
			}
		}

		//Move all ai snakes
		for(std::list<Snake>::iterator it = aiSnakes.begin(); it != aiSnakes.end(); it++){
			(*it).GetNextMove(&gameBoard);
			(*it).Move();
			if (gameData.GetWrapping() == true){
				(*it).CheckWrap(&gameBoard);
			}
		}


		//Paint all Human Snakes
		std::list<Snake>::iterator it = humanSnakes.begin(); 
		while(it != humanSnakes.end()){
			char pickupChar = gameBoard.GetChar((*it).GetRow(), (*it).GetCol());
			if(gameBoard.CheckPosition((*it).GetRow(), (*it).GetCol()) == false){
				gameBoard.AddChar((*it).GetSymbol(), (*it).GetColor(), (*it).GetRow(), (*it).GetCol());
				it++;
			}
			else if(pickupChar == 't'){
				(*it).ProcessPickup(pickupChar, &gameBoard);
				gameBoard.AddChar((*it).GetSymbol(), (*it).GetColor(), (*it).GetRow(), (*it).GetCol());
				it++;
			}
			else if(pickupChar == 'o'){
			}
			else{
				humanSnakes.erase(it++);
			}
			
		}

		//Paint all ai Snakes
		it = aiSnakes.begin(); 
		while(it != aiSnakes.end()){
			char pickupChar = gameBoard.GetChar((*it).GetRow(), (*it).GetCol());
			if(gameBoard.CheckPosition((*it).GetRow(), (*it).GetCol()) == false ){
				gameBoard.AddChar((*it).GetSymbol(), (*it).GetColor(), (*it).GetRow(), (*it).GetCol());
				it++;
			}	
			else if(pickupChar == 't'){
				(*it).ProcessPickup(pickupChar, &gameBoard);
				gameBoard.AddChar((*it).GetSymbol(), (*it).GetColor(), (*it).GetRow(), (*it).GetCol());
				it++;
			}
			else {
				aiSnakes.erase(it++);
			}
		}

		gameBoard.Paint();

		//Check for gameover	
		if ((humanSnakes.size() + aiSnakes.size() < 2) || (humanSnakes.size() < 1 && humanNumber !=0)){

			if(humanSnakes.size() != 0){
				std::list<Snake>::iterator it = humanSnakes.begin(); 
				gameData.UpdateScore((*it).GetId(), 1);
			} else {
				std::list<Snake>::iterator it = aiSnakes.begin(); 
				gameData.UpdateScore((*it).GetId(), 1);
			}
			
			humanSnakes.clear();
			aiSnakes.clear();
			
			usleep(2000000);
			gameBoard.ClearScreen();
			
			exit = 1;

		}
		usleep(gameData.GetGameSpeed());

	}while(exit == 0);

	
}

void Game::DisplayScore(){

	Menu menu(&gameData);
	
	string displayScoreString = "";
	if (gameData.GetHumanNumber() > 0){
		displayScoreString = displayScoreString + "P1: " + toString(gameData.GetScore(11));
	}
	if (gameData.GetHumanNumber() > 1){
		displayScoreString = displayScoreString + " P2: " + toString(gameData.GetScore(12));
	}
	if (gameData.GetHumanNumber() > 2){
		displayScoreString = displayScoreString + " P3: " + toString(gameData.GetScore(13));
	}
	if (gameData.GetHumanNumber() > 3){
		displayScoreString = displayScoreString + " P4: " + toString(gameData.GetScore(14));
	}
	if (gameData.GetAINumber() > 0){
		displayScoreString = displayScoreString + " AI: " + toString(gameData.GetScore(20));
	}

	MenuPanel score(displayScoreString);

	// Main Panel Items
	GameData::FunctionPointerBool setPlay = &GameData::SetPlay;
	GameData::FunctionPointerBool setExit = &GameData::SetExit;
	MenuItem playItem("Continue", true, NULL, NULL, &gameData, setPlay);
	MenuItem exitItem("Exit", true, NULL, NULL, &gameData, setExit);

	score.AddItem(&playItem);
	score.AddItem(&exitItem);
	
	//Start the Menu
	menu.SetActivePanel(&score);
	menu.Refresh();

	// CleanUp
	menu.Clear();


}


