
#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include "MenuPanel.h"
#include "GameData.h"

using namespace std;

class MenuPanel;

class MenuItem {

	public:

		MenuItem(string name, int value, MenuPanel* nPanel, MenuPanel* bPanel);
		MenuItem(string name, int value, MenuPanel* nPanel, MenuPanel* bPanel, GameData* gData, void (GameData::*FunctionPointerInt)(int));
		MenuItem(string name, bool value, MenuPanel* nPanel, MenuPanel* bPanel, GameData* gData, void (GameData::*FunctionPointerBool)(bool));
		~MenuItem();

		string GetName();

		void UpdateValue();

		MenuPanel* GetNextPanel();
		void SetNextPanel(MenuPanel* nPanel);
		MenuPanel* GetBackPanel();
		void SetBackPanel(MenuPanel* bPanel);


	private:

		MenuPanel* nextPanel;
		MenuPanel* backPanel;

		GameData* gameData;
		GameData::FunctionPointerInt intFunction;
		GameData::FunctionPointerBool boolFunction;

		string itemName;
		int itemValue;
		bool itemBool;

};

#endif
