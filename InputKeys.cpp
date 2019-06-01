

#include <iostream>
#include <ncurses.h>

#include "InputKeys.h"


InputKeys::InputKeys(){

	readTimeout = -1;
}

InputKeys::~InputKeys(){

	clear();

}

void InputKeys::SetTimeout(int timeout){
	readTimeout = timeout;
}

void InputKeys::AddKey(int key){

	keys.insert(keys.end(), key);
}

int InputKeys::GetInputKey(){

	int returnKey = -1;
	int validInput = 0;
	timeout(readTimeout);
	while(!validInput){
		int inputKey = getch();
		if (inputKey == ERR){
			return -1;
		} else{
			for(std::list<int>::iterator it = keys.begin(); it != keys.end(); it++){
				if(inputKey == *it){
					returnKey = inputKey;
					validInput = 1;
					break;
				}
			}
			if (keys.size() == 0){
				returnKey = inputKey;
				validInput = 1;
			}
		}
	}

	return returnKey;
}

void InputKeys::ClearKeys(){

	keys.clear();
}

void InputKeys::ClearBuffer(){
	
	while(getch() != ERR){
		getch();	
	}
}


