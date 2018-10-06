#ifndef GENERATOR_H
#define GENERATOR_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <bitset>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

class generator {

	private:

	public:
		generator();	//default constructor
		void generateArrivalTimes(double lambdaA, double lambdaC, vector<double> &a, vector<double> &c);
		//creates the exponential distribution

}
#endif //GENERATOR_H
