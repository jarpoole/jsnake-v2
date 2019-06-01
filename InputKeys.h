

#ifndef INPUTKEYS_H
#define INPUTKEYS_H

#include <list>

using namespace std;

class InputKeys {

	public:

		InputKeys();
		~InputKeys();
	
		void SetTimeout(int timeout);	
		void AddKey(int key);
		int GetInputKey();
		void ClearKeys();
		void ClearBuffer();

	private:

		int readTimeout;

		std::list<int> keys;

};

#endif
