#ifndef PARALLEL_H
#define PARALLEL_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <bitset>
#include <stdio.h>
#include <math.h>

using namespace std;

class parallel {

private: 
	float lambdaA;
	float lambdaC;
	float CW0;
	float DIFS;
	float SIFS;
	float ACK;
	
	

public: 
	
	parallel ();	//default constructor
	
	void uniformDistribution();//creates the uniform dsitribution 
	void exponentialDistibution(); //creates the exponential distribution
	
	
	
};

#endif //PARALLEL_H
