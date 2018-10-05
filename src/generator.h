#ifndef GENERATOR_H
#define GENERATOR_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <bitset>
#include <stdio.h>
#include <math.h>

using namespace std;

class generator {

private: 
	float lambdaA;
	float lambdaC;
	float CW0;
	float DIFS;
	float SIFS;
	float ACK;
	
	

public: 
	
	generator ();	//default constructor
	
	void uniformDistribution();//creates the uniform dsitribution 
	void exponentialDistibution(); //creates the exponential distribution
	
	
	
};

#endif //GENERATOR_H
