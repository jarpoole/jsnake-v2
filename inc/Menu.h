
#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include "Display.h"
#include "InputKeys.h"

#include "MenuPanel.h"
#include "MenuItem.h"
#include "GameData.h"

using namespace std;

class Menu{

	public:

		Menu( GameData* gData);
		~Menu();
		void Refresh();
		void SetActivePanel(MenuPanel* mainPanel);


		void Clear();
	
	private:


		void ProcessInputKey(int inputKey);
		void ProcessKeyReturn();
		void ProcessKeyBack();
		void ProcessKeyUp();
		void ProcessKeyDown();

		int selectedItem;

		Display menuDisplay;
		MenuItem* activeItem;
		MenuPanel* activePanel;
		GameData* gameData;
		InputKeys menuKeys;





		
};

#endif
