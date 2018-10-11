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

 Simulation concurrentSim;


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
    list<Station*> temp = concurrentSim.getStations();
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getSlotList() <= concurrentSim.getGlobalClk() && (*it)->getSlotList()!=0 && !(*it)->getrdyToTransmit()) {
            (*it)->setrdyToTrans();
            (*it)->randBackOffTime();
            (*it)->setDIFSTimer(concurrentSim.getDIFS());
        }
    }
    return 0;
}

list<Station*> getListofReadyNdoestrans(){ // iterates through nodes and finds nodes
    list<Station*> ready;
    list<Station*>::iterator it;
    list<Station*> temp = concurrentSim.getStations();

    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getrdyToTransmit() == true) {
            ready.push_back(*it);
        }
    }
    return ready;
}

Station* nodeToTransmit(){  // finds a node that is ready to transmit
    Station* node = NULL;
    list<Station*>::iterator it;
    list<Station*> temp = concurrentSim.getStations();
    
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getrdyToTransmit() == true && (*it)->getBackOffTime() == 0) {
            node = *it;
            break;
        }
    }
    return node;
}

void startTransmit(){
    Station* node = nodeToTransmit();  // // finds a node that is ready to transmit
    //change line status true
    concurrentSim.setLineBusy();
    // add DIFS and Back off time
    //transmit
    //add transmission durration
    concurrentSim.incGlobalClk(concurrentSim.getTranTime());
    //add SIFS and Ack to global clock
    concurrentSim.incGlobalClk(concurrentSim.getSIFS());
    concurrentSim.incGlobalClk(concurrentSim.getACK());
    
    // pop slot_list
    node->popList();
    
    //turn of transmission for line and node
    node->setnotrdyToTrans();
    concurrentSim.setLineNotBusy();
    
    return;
}

//test time creation
int random_time(){int time = (rand() % (50000 - 0)) + 1; return time;}

void simulate(int lambdaA, int lambdaC, Station* A, Station* C){
    generateArrivalTimes(lambdaA, lambdaC, (A->getpointSlotList()), (C->getpointSlotList()));
    A->makeList();
    C->makeList();
    while (concurrentSim.getGlobalClk()< 50000) {
        // check for line status
        if (concurrentSim.checkifLineIsBusy()==false) { // checks line status
            // check for packets to send
            checkTransmitTimeperNode(); // checks nodes slot list against global time for incoming packet and sets readyToTransmit on node to true
        }
        if (getListofReadyNdoestrans().size()>0  && concurrentSim.checkifLineIsBusy()==false) { // only goes in if line is not busy and there is a node ready to transmit
            // start back off time
            concurrentSim.deincrimentBackoffTime();
            // start DIFS
            concurrentSim.deincrimentDIFS();
            // check for colision
            if (concurrentSim.checkForStationsReadytoTrans().size()>1) {
                concurrentSim.incCollisionCounter(1);
                list<Station*>::iterator it;
                list<Station*> temp = concurrentSim.checkForStationsReadytoTrans();
                // update back off time
                for (it = temp.begin(); it != temp.end(); ++it){
                    (*it)->doubleContention(concurrentSim.getK());
                }
                concurrentSim.incrK();
                concurrentSim.incGlobalClk(100 +concurrentSim.getSIFS());
            }
            // start transmission
            if (concurrentSim.checkForStationsReadytoTrans().size()==1) {
                concurrentSim.startTrans();
            }
            // SIFS and ACK
        }
        if (concurrentSim.checkifLineIsBusy()==true) {
            concurrentSim.incPacketsThrough();
            //check if tranmission over
            if (concurrentSim.checkPacketsthrough()) {
                //check if successful
                //deicrment sifs and ack
                if (concurrentSim.getSIFSCounter() != 0) {
                    concurrentSim.deincSIFS();
                }
                if (concurrentSim.getSIFSCounter() == 0) {
                    concurrentSim.deincAck();
                }
                //line not busy
                if (concurrentSim.getSIFSCounter() == 0 && concurrentSim.getAckCounter() == 0) {
                    concurrentSim.setLineNotBusy();
                    //reset node
                    concurrentSim.resetNode();
                    concurrentSim.resetK();
                }
                // successful transmission
            }
        }
        concurrentSim.incGlobalClk(1); // incriments global clock by one
    }
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
    concurrentSim.setStations(Nodes);
    
    A.in_range_Create(&B); // create in range
    A.in_range_Create(&C);
    A.in_range_Create(&D);
    B.in_range_Create(&A);
    B.in_range_Create(&C);
    B.in_range_Create(&D);
    C.in_range_Create(&A);
    C.in_range_Create(&B);
    C.in_range_Create(&D);
    D.in_range_Create(&A);
    D.in_range_Create(&B);
    D.in_range_Create(&C);
    
    A.connection_Create(&B); // create transmission connections
    C.connection_Create(&D);
    
    int lambdaA = 50;
    int lambdaC = 50;
    simulate(lambdaA, lambdaC, &A, &C);
    cout << "Lambda A = "<<lambdaA<<"\n";
    cout << "Lambda C = "<<lambdaC<<"\n";
    cout << "Collisions: " << concurrentSim.getcollisioncounter() << "\n";
    cout << "A Counter: " << A.getTransmissionsThrough() << "\n";
    cout << "C Counter: " << C.getTransmissionsThrough() << "\n";
    
    return 0;
}

