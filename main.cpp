//
//  main.cpp
//  Proj_1
//
//  Created by Alec Foster on Thursday10/4.
//  Copyright © 2018 Alec Foster. All rights reserved.
//

#include <iostream>
#include "Station_Creation.hpp"
#include "Sim.hpp"

using namespace std;

 Simulation concurrentSim;



int checkTransmitTimeperNode(){ // gets next slot time from each node in slot_List and sets ready to transmit to true if it is eaqual or less than to the global clock
    list<Station*>::iterator it;
    list<Station*> temp = concurrentSim.getStations();
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getSlotList() <= concurrentSim.getGlobalClk() && (*it)->getSlotList()!=0) {
            (*it)->setrdyToTrans();
        }
    }
    return 0;
}

list<Station*> checkNodeTransmit(){ // iterates through nodes and finds nodes
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
        if ((*it)->getrdyToTransmit() == true) {
            node = *it;
            break;
        }
    }
    return node;
}

void startTransmit(){
    Station* node = nodeToTransmit();
    //change line status ture
    concurrentSim.setLineBusy();
    //add DIFS and Back off time
    concurrentSim.incGlobalClk(concurrentSim.getDIFS());
    concurrentSim.incGlobalClk(node->backOffTime());
    // check other nodes if they want to transmit during this time
    checkTransmitTimeperNode();
    if (checkNodeTransmit().size()>1) {
        concurrentSim.setCollisionCounter(1);//incriment collision
    }
    //transmit
    //seize medium
    concurrentSim.setLineBusy();
    
    //add transmission durration
    concurrentSim.incGlobalClk(concurrentSim.getTranTime());
    //add SIFS and Ack
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
    
    //Test values
    for (int i = 0; i <100; i++) {
        A.add_Slot_to_List(random_time());
        B.add_Slot_to_List(random_time());
    }
    
    A.sort_list();
    B.sort_list();
     //end test values
    

    
    
    while (concurrentSim.getGlobalClk()< 50000) {
        checkTransmitTimeperNode();
        if (concurrentSim.getLineStatus()==false) {  // checks line status
            while (!checkNodeTransmit().empty()) {
                if (checkNodeTransmit().size()>1) {
                    concurrentSim.setCollisionCounter(1);//incriment collision
                }
                // start transmit
                startTransmit();
                checkTransmitTimeperNode();
            }
        }
        
        concurrentSim.incGlobalClk(1); // incriments global clock by one
    }
    return 0;
}



