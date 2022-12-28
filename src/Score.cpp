
#include "Score.h"

Score::Score(int tempId){
	id = tempId;
	score = 0;

}
Score::~Score(){

}

int Score::GetScore(){
	return score;
}

void Score::UpdateScore(int amount){
	 score = score + amount;
}

int Score::GetId(){
	return id;
}
