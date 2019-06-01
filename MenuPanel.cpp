
#include <string>
#include <list>
#include <vector>

#include "MenuPanel.h"
#include "MenuItem.h"
#include "Debug.h"


using namespace std;


MenuPanel::MenuPanel(){

	panelName = "";
	menuItems.clear();

}

MenuPanel::MenuPanel(string name){

	panelName = name;
	menuItems.clear();

}


MenuPanel::~MenuPanel(){

}

void MenuPanel::AddItem(MenuItem* object){
	menuItems.insert(menuItems.end(), object);
}

std::list<MenuItem*>* MenuPanel::GetItems(){

	return(&menuItems);

}

string MenuPanel::GetName(){

	return(panelName);

}

int MenuPanel::MaxList(){

	return(menuItems.size());

}

