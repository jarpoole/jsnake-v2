

#include "GameData.h"
#include "Debug.h"
#include "Score.h"

GameData::GameData(){

	gameSpeed = 50000;
	wrapping = false;
	
	humanNumber = 1;
	aiNumber = 1;
	levelNumber = 1;

	play = false;
	exit = false;


}
GameData::~GameData(){

}

bool GameData::GetExit(){
	return(exit);
}

void GameData::SetExit(bool e){
	exit = e;
}

bool GameData::GetPlay(){
	return(play);
}

void GameData::SetPlay(bool p){
	play = p;
}

bool GameData::GetWrapping(){
	return(wrapping);
}

void GameData::SetWrapping(bool wrap){
	wrapping = wrap;
}

int GameData::GetGameSpeed(){
	return(gameSpeed);
}

void GameData::SetGameSpeed(int speed){
	gameSpeed = speed;
}

int GameData::GetHumanNumber(){
	return(humanNumber);
}

void GameData::SetHumanNumber(int humanNum){
	humanNumber = humanNum;
}

int GameData::GetAINumber(){
	return(aiNumber);
}

void GameData::SetAINumber(int aiNum){
	aiNumber = aiNum;
}

int GameData::GetLevel(){
	return(levelNumber);
}

void GameData::SetLevel(int level){
	levelNumber = level;
}




int GameData::GetScore(int id){
	for(std::list<Score>::iterator it = snakeScores.begin(); it != snakeScores.end(); it++){
		if ((*it).GetId() == id){
			return((*it).GetScore());
		} 			
	}
}

void GameData::AddScore(int id){
	Score newScore(id);
	snakeScores.insert(snakeScores.end(), newScore);
}

void GameData::UpdateScore(int id, int amount){
	for(std::list<Score>::iterator it = snakeScores.begin(); it != snakeScores.end(); it++){
		if ((*it).GetId() == id){
			(*it).UpdateScore(amount);
		} 			
	}
}



