

#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "Display.h"
#include "Debug.h"
#include "Random.h"

using namespace std;

Display::Display(){

	int row = 0;
	int col = 0;

	getmaxyx(stdscr, row, col);
	maxRow = row;
	maxCol = col;


	displayChar  = new char*[row];
	for (int j = 0; j<row; j++){
		displayChar[j] = new char[col];
	}


	displayColor  = new int*[row];
	for (int j = 0; j<row; j++){
		displayColor[j] = new int[col];
	}


	displayUsed  = new bool*[row];
	for (int j = 0; j<row; j++){
		displayUsed[j] = new bool[col];
	}

	ClearScreen();

}




Display::~Display(){



	for (int j = 0; j<maxRow; j++){
		delete(displayChar[j]);
	}

	delete(displayChar);


	for (int j = 0; j<maxRow; j++){
		delete(displayColor[j]);
	}

	delete(displayColor);


	for (int j = 0; j<maxRow; j++){
		delete(displayUsed[j]);
	}

	delete(displayUsed);


}



void Display::CreateBorder(){

	for (int i = 0; i<maxRow; i++){
				
		AddChar(178, 1, i, 0);
		AddChar(178, 1, i, maxCol - 1);
				
		//displayUsed[i][0] = true; // Right Side Border
		//displayUsed[i][maxCol - 1] = true; // Left Side Border
		
		//displayChar[i][maxCol - 1] = 178; // Left Side Border
		//displayChar[i][0] = 178; // Right Side Border
	}


	for (int i = 0; i<maxCol; i++){
				
		AddChar(178, 1, 0, i);
		AddChar(178, 1, maxRow - 1, i);

		//displayUsed[i][0] = true; // Top Border
		//displayUsed[i][maxRow - 1] = true; // Bottom Border
		
		//displayChar[0][i] = 178; // Top Border
		//displayChar[maxRow -1][i] = 178; // Bottom Border

	}


}

void Display::DrawRectangle(char character, int startRow, int startCol, int sizeRow, int sizeCol){

	for(int i = startCol; i < (startCol + sizeCol); i++){

		for(int j = startRow; j < (startRow + sizeRow); j++){

			AddChar(character, 1, j, i);

		}

	}

}

void Display::PrintText(string text, bool verticalCenter, bool horizontalCenter, int color, int posRow, int posCol){

	int printRow;
	int printCol;

	if(verticalCenter == TRUE){
	
		printCol = (maxCol / 2) - (text.length() / 2);

	}else{
		printCol = posCol;
	}

	if(horizontalCenter == TRUE){

		printRow = maxRow / 2;

	}else{
		printRow = posRow;
	}


	for (int charNumber = 0; charNumber < text.length(); charNumber++){
		AddChar(text.at(charNumber), color, printRow, printCol + charNumber);
	}

	// Paint Everytime:  Might not be the best design
	Paint();

}

void Display::Paint(){

	for (int row = 0; row < maxRow; row++){
		for (int col = 0; col < maxCol; col++){
			move(row, col);
			attron(COLOR_PAIR(displayColor[row][col]));
			addch(displayChar[row][col]);
			attroff(COLOR_PAIR(displayColor[row][col]));
		}
	}

	// Update the network clients
	// FIXME:


	refresh();
	

}

void Display::ClearScreen(){

	for (int row = 0; row < maxRow; row++){
		for (int col = 0; col < maxCol; col++){
			displayUsed[row][col] = false; 
			displayChar[row][col] = ' '; 
			displayColor[row][col] = 0; 
		}
	}
	clear();
	Paint();

}

bool Display::CheckPosition(int row, int col){
	return displayUsed[row][col];
}

char Display::GetChar(int row, int col){
	return displayChar[row][col];
}

void Display::GetRandomChar(char randomChar, int &returnRow, int &returnCol){

	//std::vector< std::vector<int> > charPositions;
	Random rand;
	int arraySize = 0;
	int arrayPos = 0;

	for (int row = 0; row < maxRow; row++){
		for (int col = 0; col < maxCol; col++){
			if (row == returnRow && col == returnCol){
				//do nothing
			}
			else if (displayChar[row][col] == randomChar){
				arraySize++;
			}
		}

	}
	int charPos[arraySize][2];

	for (int row = 0; row < maxRow; row++){
		for (int col = 0; col < maxCol; col++){
			if (row == returnRow && col == returnCol){
				//do nothing
			}
			else if (displayChar[row][col] == randomChar){
				charPos[arrayPos][0] = row;
				charPos[arrayPos][1] = col;
				arrayPos++;

			}
		}

	}
	int returnPos = rand.GetValue(0, arraySize - 1);
	returnRow = charPos[returnPos][0];
	returnCol = charPos[returnPos][1];

}

bool Display::CheckDisplayBounds(int row, int col){

	if(row < 0 || row > maxRow || col < 0 || col > maxCol){
		return(false);
	}
	else{
		return(true);
	}

}

void Display::AddChar(char symbol, int color, int row, int col){



	displayUsed[row][col] = true; 
	displayChar[row][col] = symbol; 
	displayColor[row][col] = color; 
	
}

int Display::GetLastRow(){
	return (maxRow - 1);
}

int Display::GetLastCol(){
	return (maxCol - 1);
}

void Display::LoadLevel(int level){

	if(level == 0){
		//Splash Screen
		
		int x = (maxCol / 2) - 65;
		int y = 20;		

		PrintText(" _________ _______  _        _______  _        _______             _______  _______           _______  _        _______  _______ ", false, false, 1, y, x);	
		PrintText(" \\__    _/(  ____ \\( (    /|(  ___  )| \\    /\\(  ____ \\           (  ____ )(  ____ \\|\\     /|(  ____ \\( (    /|(  ____ \\(  ____ \\", false, false, 1, y + 1, x);	
		PrintText("    )  (  | (    \\/|  \\  ( || (   ) ||  \\  / /| (    \\/           | (    )|| (    \\/| )   ( || (    \\/|  \\  ( || (    \\/| (    \\/", false, false, 1, y + 2, x);	
		PrintText("    |  |  | (_____ |   \\ | || (___) ||  (_/ / | (__       _____   | (____)|| (__    | |   | || (__    |   \\ | || |      | (__    ", false, false, 1, y + 3, x);	
		PrintText("    |  |  (_____  )| (\\ \\) ||  ___  ||   _ (  |  __)     (_____)  |     __)|  __)   ( (   ) )|  __)   | (\\ \\) || | ____ |  __)   ", false, false, 1, y + 4, x);	
		PrintText("    |  |        ) || | \\   || (   ) ||  ( \\ \\ | (                 | (\\ (   | (       \\ \\_/ / | (      | | \\   || | \\_  )| (      ", false, false, 1, y + 5, x);	
		PrintText(" |\\_)  )  /\\____) || )  \\  || )   ( ||  /  \\ \\| (____/\\           | ) \\ \\__| (____/\\  \\   /  | (____/\\| )  \\  || (___) || (____/\\", false, false, 1, y + 6, x);	
		PrintText(" (____/   \\_______)|/    )_)|/     \\||_/    \\/(_______/           |/   \\__/(_______/   \\_/   (_______/|/    )_)(_______)(_______/", false, false, 1, y + 7, x);	
		
		PrintText("Designed and programmed by Jared Poole", true, false, 1, y + 12, 0);

	}


	else if(level == 1){
		//Nothing (Blank Board)
	}
	else if(level == 2){
	
		int posY = maxRow / 3;
		int posX = maxCol / 19;

		for (int rectCount = 1; rectCount < 7; rectCount++){
			DrawRectangle('H', posY, (posX * (rectCount * 3)), 5, 5);
		}

		for (int rectCount = 1; rectCount < 7; rectCount++){
			DrawRectangle('H', posY * 2, (posX * (rectCount * 3)), 5, 5);
		}

		for (int i = 0; i<maxCol; i++){

			AddChar(178, 1, 0, i);
			AddChar(178, 1, maxRow - 1, i);
		}
	}
	else if(level == 3){
		int posY = maxRow / 5;
		int posX = maxCol / 5;

		DrawRectangle('H', posY, posX, 3, posX * 3);
		DrawRectangle('H', posY * 4, posX, 3, posX * 3);
		DrawRectangle('H', posY, (maxCol / 2 - 1), posY * 3, 3);

		
	}
	else if(level == 4){
		int spacing = 4;

		//Outside sides
		for(int i = 0; i < (maxRow / 2) - spacing; i++){
			AddChar(178, 1, i, 0);
		}
		for(int i = (maxRow / 2) + spacing; i < maxRow; i++){
			AddChar(178, 1, i, 0);
		}
		
		for(int i = 0; i < (maxRow / 2) - spacing; i++){
			AddChar(178, 1, i, maxCol - 1);
		}
		for(int i = (maxRow / 2) + spacing; i < maxRow; i++){
			AddChar(178, 1, i, maxCol - 1);
		}

		//Outside top and bottom
		for(int i = 0; i < (maxCol / 2) - spacing; i++){
			AddChar(178, 1, 0, i);
		}
		for(int i = (maxCol / 2) + spacing; i < maxCol; i++){
			AddChar(178, 1, 0, i);
		}
		
		for(int i = 0; i < (maxCol / 2) - spacing; i++){
			AddChar(178, 1, maxRow - 1, i);
		}
		for(int i = (maxCol / 2) + spacing; i < maxCol; i++){
			AddChar(178, 1, maxRow - 1, i);
		}
		
		//Inside sides
		for(int i = (spacing * 2) + 1; i < (maxRow / 2) - spacing; i++){
			AddChar(178, 1, i, (spacing * 2) + 1);
		}
		for(int i = (maxRow / 2) + spacing; i < maxRow - (spacing * 2); i++){
			AddChar(178, 1, i, (spacing * 2) + 1);
		}
		
		for(int i = (spacing * 2) + 1; i < (maxRow / 2) - spacing; i++){
			AddChar(178, 1, i, maxCol - (spacing * 2) - 1);
		}
		for(int i = (maxRow / 2) + spacing; i < (maxRow - (spacing * 2) - 1); i++){
			AddChar(178, 1, i, maxCol - (spacing * 2) - 1);
		}

		//Inside top and bottom
		for(int i = (spacing * 2) + 1; i < (maxCol / 2) - spacing; i++){
			AddChar(178, 1, (spacing * 2) + 1, i);
		}
		for(int i = (maxCol / 2) + spacing; i < maxCol - (spacing * 2); i++){
			AddChar(178, 1, (spacing * 2) + 1, i);
		}
		
		for(int i = (spacing * 2) + 1; i < (maxCol / 2) - spacing; i++){
			AddChar(178, 1, maxRow - (spacing * 2) - 1, i);
		}
		for(int i = (maxCol / 2) + spacing; i < maxCol - (spacing * 2); i++){
			AddChar(178, 1, maxRow - (spacing * 2) - 1, i);
		}
		AddChar('t', 1, 20, 20);
		AddChar('t', 1, maxRow - 20, maxCol - 20);

	}

	else if(level == 5){
		DrawRectangle('X', 0, maxCol / 3 + 12, maxRow, 4);
		DrawRectangle('X', 0, (maxCol / 3) * 2 - 16, maxRow, 4);

		AddChar('t', 1, 20, maxCol / 2);
		AddChar('t', 1, maxRow - 20, maxCol / 2);
		AddChar('t', 1, 20, maxCol / 6 + 4);
		AddChar('t', 1, maxRow - 20, maxCol / 6 + 4);
		AddChar('t', 1, 20, (maxCol / 6) * 5 - 4);
		AddChar('t', 1, maxRow - 20, (maxCol / 6) * 5 - 4);
		
	}
}







