//
//  generator.hpp
//  Proj_1
//
//  Created by Alec Foster on Tuesday10/9.
//  Copyright © 2018 Alec Foster. All rights reserved.
//

#ifndef generator_hpp
#define generator_hpp

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
    generator();    //default constructor
    void generateArrivalTimes(double lambdaA, double lambdaC, vector<double> &a, vector<double> &c);
    //creates the exponential distribution
    
};
#endif //GENERATOR_H
