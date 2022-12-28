

#include <iostream>

#include "Snake.h"
#include "Random.h"
#include "Debug.h"


Snake::Snake(bool isAI, char sSymbol, int sColor, int startRow, int startCol, int sID, int mLeft, int mRight, int mUp, int mDown ){

	symbol = sSymbol;
	ai = isAI;
	color = sColor;
	id = sID;

	currentRow = startRow;
	currentCol = startCol;


	Random rand;
	int startDirection = rand.GetValue(1, 4);

	if(startDirection == 1){
		currentRowDirection = 1;
		currentColDirection = 0;
	} 
	else if (startDirection == 2){
		currentRowDirection = -1;
		currentColDirection = 0;
	} 
	else if (startDirection == 3){
		currentRowDirection = 0;
		currentColDirection = 1;
	} 
	else{
		currentRowDirection = 0;
		currentColDirection = -1;
	} 

	moveLeft = mLeft;
	moveRight = mRight;
	moveUp = mUp;
	moveDown = mDown;

}

Snake::~Snake(){

}

int Snake::GetRow(){
	return currentRow;
}

int Snake::GetCol(){
	return currentCol;
}

char Snake::GetSymbol(){
	return symbol;
}

int Snake::GetColor(){
	return color;
}

int Snake::GetKeyLeft(){
	return moveLeft;
}

int Snake::GetKeyRight(){
	return moveRight;
}

int Snake::GetKeyUp(){
	return moveUp;
}

int Snake::GetKeyDown(){
	return moveDown;
}

int Snake::GetId(){
	return id;
}

void Snake::SetRow(int row){
	currentRow = row;
}
void Snake::SetCol(int col){
	currentCol = col;
}

void Snake::GetNextMove(Display* gameBoard){

	Random rand;

	int maxRow = gameBoard->GetLastRow();
	int maxCol = gameBoard->GetLastCol();

	int localRow = currentRow;
	int localCol = currentCol;


	if(currentRow == gameBoard->GetLastRow() && currentRowDirection == 1){
		localRow = 0;
	}
	else if(currentRow == 0 && currentRowDirection == -1){
		localRow = gameBoard->GetLastRow();
	}

	int checkRowUp = localRow - 1;
	int checkRowDown = localRow + 1;
	int checkColLeft = localCol - 1;
	int checkColRight = localCol + 1;

	if(checkRowUp < 0){
		checkRowUp = maxRow;
	}
	if(checkRowDown > maxRow){
		checkRowDown = 0;
	}
	if(checkColLeft < 0){
		checkColLeft = maxCol;
	}
	if(checkColRight > maxCol){
		checkColRight = 0;
	}



	if(gameBoard->CheckPosition(localRow, checkColRight) != false &&
		gameBoard->CheckPosition(localRow, checkColLeft) != false &&
		gameBoard->CheckPosition(checkRowUp, localCol) != false &&
		gameBoard->CheckPosition(checkRowDown, localCol) != false){

		// Do Nothing

	}
	else if (currentColDirection == 1 && gameBoard->CheckPosition(localRow, localCol + 1) != false){
		do{

			currentRowDirection = rand.GetDirection();
			currentColDirection = 0;
		
		}while(currentRowDirection == 0 || gameBoard->CheckPosition(localRow + currentRowDirection, localCol) != false);
	
	}	

	else if (currentColDirection == -1 && gameBoard->CheckPosition(localRow, localCol - 1) != false){
		do{

			currentRowDirection = rand.GetDirection();
			currentColDirection = 0;
		
		}while(currentRowDirection == 0 || gameBoard->CheckPosition (localRow + currentRowDirection, localCol) != false);
	}	

	else if (currentRowDirection == 1 && gameBoard->CheckPosition(localRow + 1, localCol) != false){
		do{

			currentRowDirection = 0;
			currentColDirection = rand.GetDirection();
		
		}while(currentColDirection == 0 || gameBoard->CheckPosition(localRow, localCol + currentColDirection) != false);
	}

	else if (currentRowDirection == -1 && gameBoard->CheckPosition(localRow - 1, localCol) != false){
		do{

			currentRowDirection = 0;
			currentColDirection = rand.GetDirection();
		
		}while(currentColDirection == 0 || gameBoard->CheckPosition(localRow, localCol + currentColDirection) != false);
	}	

}

void Snake::Move(){
	currentRow = currentRow + currentRowDirection;
	currentCol = currentCol + currentColDirection;
}

void Snake::CheckWrap(Display* gameBoard){

		if(currentRow == gameBoard->GetLastRow() + 1 ){
			currentRow = 0;
		}
		else if(currentRow == -1){
			currentRow = gameBoard->GetLastRow();
		}

		if(currentCol == gameBoard->GetLastCol() + 1 ){
			currentCol = 0;
		}
		else if(currentCol == -1){
			currentCol = gameBoard->GetLastCol();
		}

}

void Snake::ProcessInput(int key){

	if(key == moveLeft && currentColDirection != 1){
		currentRowDirection = 0;
		currentColDirection = -1;
	} 
	else if (key == moveRight && currentColDirection != -1){
		currentRowDirection = 0;
		currentColDirection = 1;
	}
	else if(key == moveUp && currentRowDirection != 1){
		currentRowDirection = -1;
		currentColDirection = 0;
	} 
	else if(key == moveDown && currentRowDirection != -1){
		currentRowDirection = 1;
		currentColDirection = 0;
	}

}

void Snake::ProcessPickup(char pickupChar, Display* gameBoard){
	
	if(pickupChar == 't'){
		
		while(1){
			int row = currentRow;
			int col = currentCol;
			gameBoard->GetRandomChar('t', row, col);
		
			if (gameBoard->CheckPosition(row + currentRowDirection, col + currentColDirection) == false){
		
				currentRow = row;
				currentCol = col;
				Move();
				break;
			}
		}
	}

}







