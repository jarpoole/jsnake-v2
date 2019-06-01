#ifndef SCORE_H
#define SCORE_H


class Score {

	public:
		Score(int tempId);
		~Score();
		
		int GetScore();
		void UpdateScore(int amount);
		int GetId();

	private:
		int score;
		int id;		

};

#endif
