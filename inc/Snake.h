

#ifndef SNAKE_H
#define SNAKE_H

#include "Display.h"

class Snake {

	public:
		Snake(bool isAI, char sSymbol, int sColor, int startRow, int startCol, int sID, int mLeft, int mRight, int mUp, int mDown );
		~Snake();

		int GetRow();
		int GetCol();
		char GetSymbol();
		int GetColor();
		int GetId();

		void Move();

		int GetKeyLeft();
		int GetKeyRight();
		int GetKeyUp();
		int GetKeyDown();

		void SetRow(int row);
		void SetCol(int col);

		void ProcessInput(int key);
		void GetNextMove(Display* gameBoard);
		void CheckWrap(Display* gameBoard);
		void ProcessPickup(char pickupChar, Display* gameBoard);

	private:

		char symbol;
		bool ai;
		int color;
		int id;
	
		int currentRow;
		int currentCol;
		int currentRowDirection;
		int currentColDirection;

		int moveLeft;
		int moveRight;
		int moveUp;
		int moveDown;
		


};

#endif
