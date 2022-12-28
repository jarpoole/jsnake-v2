
#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Debug{

	public:

		Debug();
		~Debug();

		static void Print(string debug);
		static void Print(int debug);
	
	private:

		
};

#endif
