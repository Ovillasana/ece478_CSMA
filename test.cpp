//
//  test.cpp
//  Proj_1
//
//  Created by Alec Foster on Friday10/12.
//  Copyright © 2018 Alec Foster. All rights reserved.
//

#include "test.hpp"
#include "Station_Creation.hpp"
#include "Sim.hpp"
#include <iostream>

using namespace std;


Station testS;

void createTest(){
    Simulation testSim;
    Station A,B,C;
    list<Station*> Nodes;
    A.station_Create('A'); // create stations
    B.station_Create('B');
    C.station_Create('C');
    Nodes.push_back(&A);
    Nodes.push_back(&B);
    Nodes.push_back(&C);
    
    //concurrent simulation
    testSim.setStations(Nodes); // concurrent with out virtual carrier sensing
    //createConectionsSim1(&A, &B, &C, &D); // concurrent
    A.in_range_Create(&B);
    A.connection_Create(&B);
    C.in_range_Create(&B);
    C.connection_Create(&B);
    B.in_range_Create(&A);
    B.in_range_Create(&C);
    B.connection_Create(&A);
    B.connection_Create(&C);
    
    
    A.setStatus(testSim.getStatusat(0));
    

}
