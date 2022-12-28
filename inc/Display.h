
#ifndef DISPLAY_H
#define DISPLAY_H

class Display {

	public:
		Display();
		~Display();


		void CreateBorder();
		void PrintText(std::string text, bool verticalCenter, bool horizontalCenter, int color, int posRow, int posCol);
		void Paint();
		void ClearScreen();
		void DrawRectangle(char character, int startRow, int startCol, int sizeRow, int sizeCol);
		
		bool CheckPosition(int row, int col);
		bool CheckDisplayBounds(int row, int col);
		char GetChar(int row, int col);
		void GetRandomChar(char randomChar, int &returnRow, int &returnCol);

		void AddChar(char symbol, int color, int row, int col);
		void LoadLevel(int level);

		int GetLastRow();
		int GetLastCol();


	private:

		int maxRow;
		int maxCol;

		bool** displayUsed;
		char** displayChar;
		int** displayColor;
		

};

#endif
