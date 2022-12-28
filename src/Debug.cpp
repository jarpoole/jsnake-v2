
#include <string>
#include "Debug.h"

using namespace std;

static ofstream debugFile;

Debug::Debug(){

	ofstream debugFile;
	debugFile.open("debug.tmp");
	debugFile.close();

}

Debug::~Debug(){


}

void Debug::Print(string debug){

	ofstream debugFile;
	debugFile.open("DEBUG",ios::out | ios::app );
	debugFile << debug << "\n";
	debugFile.close();

}

void Debug::Print(int debug){

	ofstream debugFile;
	debugFile.open("DEBUG",ios::out | ios::app );
	debugFile << debug << "\n";
	debugFile.close();

}


