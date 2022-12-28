
#include <vector>
#include <string>
#include <ncurses.h>

#include "Display.h"
#include "InputKeys.h"
#include "Menu.h"
#include "MenuPanel.h"
#include "MenuItem.h"
#include "Debug.h"
#include "GameData.h"

#include "Constants.h"

using namespace std;

Menu::Menu( GameData* gData){

	menuKeys.SetTimeout(-1);

	menuKeys.AddKey(KEY_UP);
	menuKeys.AddKey(KEY_DOWN);
	menuKeys.AddKey(KEY_RETURN);
	menuKeys.AddKey(KEY_BACK);

	selectedItem = 0;
	activeItem = NULL;

	gameData = gData;
}

Menu::~Menu(){

}

void Menu::SetActivePanel(MenuPanel* mainPanel){

	activePanel = mainPanel;
	activeItem = NULL;
	selectedItem = 0;
}

void Menu::Clear(){
	menuDisplay.ClearScreen();

}


void Menu::Refresh(){


	do{


		int count = 0;
		menuDisplay.PrintText(activePanel->GetName(), true, false, 1, 19, 0);

		for(std::list<MenuItem*>::iterator it = (activePanel->GetItems())->begin(); it != (activePanel->GetItems())->end(); it++){
			
			if(count == selectedItem){
				menuDisplay.PrintText((*it)->GetName(), true, false, 10, 21 + count, 20);
				activeItem = (*it);
			} else {
				menuDisplay.PrintText((*it)->GetName(), true, false, 1, 21 + count, 20);
			}
			count++;
		}
		menuDisplay.Paint();

		int inputKey = menuKeys.GetInputKey();
		ProcessInputKey(inputKey);


	} while(gameData->GetPlay() == false && gameData->GetExit() == false);


}

void Menu::ProcessInputKey(int inputKey){

	if(inputKey == KEY_RETURN){
		ProcessKeyReturn();
	}
	else if(inputKey == KEY_BACK){
		ProcessKeyBack();
	}
	else if(inputKey == KEY_UP){
		ProcessKeyUp();
	}
	else if(inputKey == KEY_DOWN){
		ProcessKeyDown();
	}
 	else {
		// Error: Should not get here
	}
}

void Menu::ProcessKeyReturn(){

	if(activeItem->GetNextPanel() != NULL){
		// We want to move to next panel
		menuDisplay.ClearScreen();
		activePanel = activeItem->GetNextPanel();
	} else {
		activeItem->UpdateValue();
	}

}

void Menu::ProcessKeyBack(){

	if(activeItem->GetBackPanel() != NULL){
		menuDisplay.ClearScreen();
		activePanel = activeItem->GetBackPanel();
	}

}

void Menu::ProcessKeyUp(){

	if(selectedItem > 0) {
		selectedItem--;
	} else {
		selectedItem = 0;
	}

}

void Menu::ProcessKeyDown(){
	
	int maxList = activePanel->MaxList() - 1;
	if(selectedItem < maxList){
		selectedItem++;
	} else {
		selectedItem = maxList;
	}
}


