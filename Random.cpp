

#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "Random.h"

using namespace std;

Random::Random(){
}

Random::~Random(){
}

int Random::GetValue(int lower, int upper){

	
	int difference = (upper - lower) + 1;
	int answer = (rand() %difference) + lower;	
	return(answer);

}

int Random::GetDirection(){

	int answer = (rand() %2);	
	if(answer != 1){
		answer = -1;
	}
	return(answer);

}

