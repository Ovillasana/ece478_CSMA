//
//  main.cpp
//  Proj_1
//
//  Created by Alec Foster on Thursday10/4.
//  Copyright © 2018 Alec Foster. All rights reserved.
//

#include "Station_Creation.hpp"
#include "Sim.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

 Simulation concurrentSim1;


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



int checkTransmitTimeperNode(){ // gets next slot time from each node in slot_List and sets ready to transmit to true if it is eaqual or less than to the global clock
    list<Station*>::iterator it;
    list<Station*> temp = concurrentSim1.getStations();
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getSlotList() <= concurrentSim1.getGlobalClk()) {
            if ((*it)->getSlotList()!=0) {
                if ((*it)->getStatusNode() == "Idle") {
                    if ((*it)->getBackOffTime()==0) {
                        (*it)->randBackOffTime();
                    }
                    (*it)->setrdyToTrans();
                    (*it)->setDIFSTimer(concurrentSim1.getDIFS());
                    (*it)->setStatus(concurrentSim1.getStatusat(2));
                }
            }
            if (concurrentSim1.getRTSCTS()) {
                if ((*it)->getStatusNode() == "RTS") {
                    if ((*it)->getRTSCounter()==0) {
                        
                    }
                }
            }
        }
    }
    return 0;
}

list<Station*> getListofReadyNdoestrans(){ // iterates through nodes and finds nodes
    list<Station*> ready;
    list<Station*>::iterator it;
    list<Station*> temp = concurrentSim1.getStations();

    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getrdyToTransmit() == true) {
            ready.push_back(*it);
        }
    }
    return ready;
}

list<Station*> nodesToTransmit(){  // finds a node that is ready to transmit
    list<Station*> nodes;
    list<Station*>::iterator it;
    list<Station*> temp = concurrentSim1.getStations();
    
    if (concurrentSim1.getRTSCTS()) {
        for (it = temp.begin(); it != temp.end(); ++it){
            if ((*it)->getrdyToTransmit() == true && (*it)->getBackOffTime() == 0 && (*it)->getRTSCounter() == 0) {
                if (!(*it)->getCTSRec()) {
                    (*it)->setRTSCounter();
                }
                
                nodes.push_back(*it);
            }
        }
    }
    else{
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getrdyToTransmit() == true && (*it)->getBackOffTime() == 0) {
            nodes.push_back(*it);
        }
    }
    }
    return nodes;
}

void startTransmit(){
    
    
    return;
}

//test time creation
int random_time(){int time = (rand() % (50000 - 0)) + 1; return time;}

void simulate(int lambdaA, int lambdaC, Station* A, Station* C, int val){
    if (val) {
        concurrentSim1.setRTSCTS();
    }
    generateArrivalTimes(lambdaA, lambdaC, (A->getpointSlotList()), (C->getpointSlotList()));
    A->makeList();
    C->makeList();
    while (concurrentSim1.getGlobalClk()< 50000) {
        concurrentSim1.deincrimentCounters();
        concurrentSim1.updateStatus();
        //collision check
        concurrentSim1.collisionCheck();
        checkTransmitTimeperNode(); //check each node for new packet
        concurrentSim1.incGlobalClk(1); // incriments global clock by one
    }
}

void createConectionsSim1(Station* A,Station* B,Station* C,Station* D){
    A->in_range_Create(B); // create in range
    A->in_range_Create(C);
    A->in_range_Create(D);
    B->in_range_Create(A);
    B->in_range_Create(C);
    B->in_range_Create(D);
    C->in_range_Create(A);
    C->in_range_Create(B);
    C->in_range_Create(D);
    D->in_range_Create(A);
    D->in_range_Create(B);
    D->in_range_Create(C);
    
    A->connection_Create(B); // create transmission connections
    C->connection_Create(D);
    B->connection_Create(A);
    D->connection_Create(C);
    
    return;
}
void createConectionsSim2(Station* A,Station* B,Station* C,Station* D){
    A->in_range_Create(B); // create in range
    B->in_range_Create(A);
    B->in_range_Create(C);
    C->in_range_Create(B);
    
    A->connection_Create(B); // create transmission connections
    C->connection_Create(B);
    B->connection_Create(A);
    B->connection_Create(C);
    
    return;
}


int main() {
    // Concurrent Comunications
    Station A,B,C,D;
    list<Station*> Nodes;
    A.station_Create('A'); // create stations
    B.station_Create('B');
    C.station_Create('C');
    D.station_Create('D');
    Nodes.push_back(&A);
    Nodes.push_back(&B);
    Nodes.push_back(&C);
    Nodes.push_back(&D);
    
    //concurrent simulation
    concurrentSim1.setStations(Nodes); // concurrent with out virtual carrier sensing  
    createConectionsSim1(&A, &B, &C, &D); // concurrent
    //createConectionsSim2(&A, &B, &C, &D); // hidden

    int lambdaA = 50;
    int lambdaC = 50;
    simulate(lambdaA, lambdaC, &A, &C, 1);
    cout << "Lambda A = "<<lambdaA<<"\n";
    cout << "Lambda C = "<<lambdaC<<"\n";
    cout << "Collisions: " << concurrentSim1.getcollisioncounter() << "\n";
    cout << "A Counter: " << A.getPacketsThrough() << "\n";
    cout << "C Counter: " << C.getPacketsThrough() << "\n";
    
    
    
    return 0;
}

