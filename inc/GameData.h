#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "Score.h"
#include <list>

class GameData{

	public:

		GameData();
		~GameData();
		
		typedef void (GameData::*FunctionPointerBool)(bool);
		typedef void (GameData::*FunctionPointerInt)(int);

		bool GetWrapping();
		void SetWrapping(bool wrap);

		bool GetExit();
		void SetExit(bool exit);

		bool GetPlay();
		void SetPlay(bool play);

		int GetGameSpeed();
		void SetGameSpeed(int speed);

		int GetLevel();
		void SetLevel(int level);

		int GetHumanNumber();
		void SetHumanNumber(int humanNum);

		int GetAINumber();
		void SetAINumber(int aiNum);

		int GetScore(int id);
		void AddScore(int id);
		void UpdateScore(int id, int amount);

	private:

		bool play;
		bool exit;

		bool wrapping;
		int gameSpeed;
		int levelNumber;

		int aiNumber;
		int humanNumber;

		int score[5];
		
		std::list<Score> snakeScores;
		
	
};


#endif
