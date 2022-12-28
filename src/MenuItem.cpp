
#include <string>
#include <string.h>

#include "MenuPanel.h"
#include "MenuItem.h"
#include "Debug.h"


using namespace std;


MenuItem::MenuItem(string name, int value, MenuPanel* nPanel, MenuPanel* bPanel){

	itemName = name;
	itemValue = value;
	itemBool = false;

	nextPanel = nPanel;
	backPanel = bPanel;

	gameData = NULL;
	intFunction = NULL;
	boolFunction = NULL;

}

MenuItem::MenuItem(string name, int value, MenuPanel* nPanel, MenuPanel* bPanel, GameData* gData, GameData::FunctionPointerInt ptr){

	itemName = name;
	itemValue = value;
	itemBool = false;

	nextPanel = nPanel;
	backPanel = bPanel;

	gameData = gData;
	intFunction = ptr;
	boolFunction = NULL;

}

MenuItem::MenuItem(string name, bool value, MenuPanel* nPanel, MenuPanel* bPanel, GameData* gData, GameData::FunctionPointerBool ptr){

	itemName = name;
	itemValue = 0;
	itemBool = value;

	nextPanel = nPanel;
	backPanel = bPanel;

	gameData = gData;
	intFunction = NULL;
	boolFunction = ptr;

}

MenuItem::~MenuItem(){

}

string MenuItem::GetName(){

	return(itemName);
}


void MenuItem::UpdateValue(){

	if(gameData != NULL){
		if(intFunction != NULL){
			(gameData->*intFunction)(itemValue);
		} 
		else if(boolFunction != NULL){
			(gameData->*boolFunction)(itemBool);
		}
	}
	return;
}


MenuPanel* MenuItem::GetNextPanel(){

	return nextPanel;

}
void MenuItem::SetNextPanel(MenuPanel* nPanel){

	nextPanel = nPanel;

}
MenuPanel* MenuItem::GetBackPanel(){

	return backPanel;

}
void MenuItem::SetBackPanel(MenuPanel* bPanel){

	backPanel = bPanel;

}
