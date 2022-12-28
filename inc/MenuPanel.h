
#ifndef MENUPANEL_H
#define MENUPANEL_H

#include <string>
#include <list>
#include "MenuItem.h"

using namespace std;

class MenuItem;

class MenuPanel {

	public:

		MenuPanel();
		MenuPanel(string name);
		~MenuPanel();
		
		void AddItem(MenuItem* object);
		std::list<MenuItem*>* GetItems();

		string GetName();
		int MaxList();


	private:


		string panelName;
		std::list<MenuItem*> menuItems;
		
};

#endif
