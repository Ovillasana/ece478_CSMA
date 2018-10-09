#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

void generateArrivalTimes(double lambdaA, double lambdaC, vector<double> &a, vector<double> &c) {

	//generating a series of uniformly distributed numbers between 0 and 1
	vector<double> Ua;
	vector<double> Uc;
	for (unsigned int i = 0; i < lambdaA * 10; i++) {
		double a = ((double)rand() / (RAND_MAX));
		double c = ((double)rand() / (RAND_MAX));
		Ua.push_back(a);
		Uc.push_back(c);
	}
	//sort vector & delete duplicates
	sort(Ua.begin(), Ua.end());
	sort(Uc.begin(), Uc.end());
	Ua.erase(unique(Ua.begin(), Ua.end()), Ua.end());
	Uc.erase(unique(Uc.begin(), Uc.end()), Uc.end());

	// Exponentially distributed generator 
	vector<double> Xa;
	vector<double> Xc;

	for (unsigned int i = 0; i < Ua.size(); i++) {
		Xa.push_back((-1 / (lambdaA)) * log(1 - Ua[i]));
	}

	for (unsigned int i = 0; i < Uc.size(); i++) {
		Xc.push_back((-1 / (lambdaC)) * log(1 - Uc[i]));
	}

	//Create arrival times for A and C 
	vector<double>timesA;
	vector<double>timesC;
	for (unsigned int i = 0; i < Xa.size(); i++) {
		timesA.push_back(Xa[i] / (2 * pow(10.0, -5.0)));
	}

	for (unsigned int i = 0; i < Xc.size(); i++) {
		timesC.push_back(Xc[i] / (2 * pow(10.0, -5.0)));
	}
	vector<double>arrivalTimesA;
	vector<double>arrivalTimesC;
	double temp = 0;
	for (unsigned int i = 0; i < Xa.size(); i++) {
		temp += timesA[i];
		arrivalTimesA.push_back(ceil(temp));
	}
	temp = 0;
	for (unsigned int i = 0; i < Xc.size(); i++) {
		temp += timesC[i];
		arrivalTimesC.push_back(ceil(temp));
	}

	a = arrivalTimesA;
	c = arrivalTimesC;
}

double RNG(int max) {
	double rngDbl = 0;
	int rngInt = (rand() % (max)) ;
	rngDbl = (double)rngInt;
	return rngDbl;
}


void simulation1(vector<double> &a, vector<double> &c) {
	double SIFS = 1;
	double DIFS = 2;
	double ACK = 2;
	double CW0 = 4;
	double CWmax = 1024;
	double collision, counterA, counterC, backoff = 0;

	long double globalTimer = 0;

	// checks which station transmits first 
	bool aFirst = false;
	bool cFirst = false;

	if (a[0] < c[0]) {
		// a transmits first
		aFirst = true;
		backoff = RNG(CW0);
		globalTimer += (a[0] + DIFS + backoff);
		//a.erase(a.begin());
	}
	
	else if (c[0] < a[0]) {
		// c transmits first
		cFirst = true;
		backoff = RNG(CW0);
		globalTimer += (c[0] + DIFS + backoff);
	}

	else if (a[0] == c[0]) {
		//collision right away
		//handle later
		globalTimer += 0;
	}

	else {}
	
	//check the i

}


int main() {

	
	for (unsigned int i = 0; i < 40; i++) {
		double temp = RNG(4);
		cout << temp << endl;
	}

	vector<double> arrivalTimesA;
	vector<double> arrivalTimesC;
	generateArrivalTimes(50, 50, arrivalTimesA, arrivalTimesC);
	cout << "testttttttt";

	//arrivalTimesA.erase(arrivalTimesA.begin());

	int abc = 0;

	return 0;
}