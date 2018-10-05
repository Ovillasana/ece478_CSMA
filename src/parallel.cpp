#include "parallel.h"

using namespace std;



parallel::parallel(){
	
}

void parallel::uniformDistribution(){
	
	
	vector<double> Ua;
	vector<double> Uc; 
		Ua[] = {idk what to put here}
		Uc[] = {idk what to put here}
}

void parallel::exponentialDistribution(){
	
	// Exponentially distribued generator 
	vector<double> Xa;
	vector<double> Xc;
	
	for(unsigned int i = 0; i < Ua.size(); i++){
		Xa.push_back = (-1/(this.lambdaA)) * log(1 - Ua[i]);
	}
	
	for(unsigned int i = 0; i < Uc.size(); i++){
		Xc.push_back = (-1/(this.lambdaC)) * log(1 - Uc[i]);
	}
	
/////////////////////////////////////////////
	
	//Create arrival times for A and C 
	vector<double>arrivalTimesA;
	vector<double>arrivalTimesC;
	 
	for (unsigned int i = 0; i < Xa.size(); i++){
		arrivalTimesA.push_back = Xa[i] / (2*pow(10.0, -5.0);
	}
	
	for (unsigned int i = 0; i < Xc.size(); i++){
		arrivalTimesA.push_back = Xc[i] / (2*pow(10.0, -5.0);
	}	
	
}

void parallel::send(){
	unsigned int counterA = 0;
	unsigned int counterC = 0;
	unsigned int collisionCounter = 0;
	
	
	
}