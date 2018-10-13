//
//  generator.cpp
//  Proj_1
//
//  Created by Alec Foster on Tuesday10/9.
//  Copyright © 2018 Alec Foster. All rights reserved.
//

#include "generator.hpp"
using namespace std;


generator::generator() {
}

void generator::generateArrivalTimes(double lambdaA, double lambdaC, vector<double> &a, vector<double> &c) {
    
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
        arrivalTimesA.push_back(temp);
    }
    temp = 0;
    for (unsigned int i = 0; i < Xc.size(); i++) {
        temp += timesC[i];
        arrivalTimesC.push_back(temp);
    }
    
    a = arrivalTimesA;
    c = arrivalTimesC;
}
