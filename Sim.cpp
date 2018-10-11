//
//  Sim.cpp
//  Proj_1
//
//  Created by Alec Foster on Friday10/5.
//  Copyright © 2018 Alec Foster. All rights reserved.
//

#include "Sim.hpp"

bool Simulation::senseDIFS(){
    if (Simulation::checkifLineIsBusy()) {
        return true;
    }
    
    return false;
}

void Simulation::deincrimentBackoffTime(){    // goes through list of stations and deindriments Backofftimer
    list<Station*>::iterator it;
    list<Station*> temp = Simulation::getStations();
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getBackOffTime() != 0 && (*it)->getDIFSTimer() == 0) {
            (*it)->subtBackOffTime();
        }
    }
    return;
}

void Simulation::deincrimentDIFS(){
    list<Station*>::iterator it;
    list<Station*> temp = Simulation::getStations();
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getDIFSTimer() != 0 && (*it)->getrdyToTransmit()) {
            (*it)->subtDIFSTimer();
        }
    }
    return;
    
}

void Simulation::senseLowestBackOffTime(){
    list<Station*>::iterator it;
    list<int> times{};
    list<Station*> temp = Simulation::getStations();
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getBackOffTime() != 0 && (*it)->getrdyToTransmit()){
            times.push_back((*it)->getBackOffTime());
        }
    }
    times.sort();
    if (!times.empty()) {
        Simulation::setLowestBackoff(times.front());
    }
    return;
}

list<Station*> Simulation::checkForStationsReadytoTrans(){
    
    list<Station*> readyToTransmit;
    list<Station*>::iterator it;
    list<Station*> temp = getStations();
    
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getrdyToTransmit() == true && (*it)->getDIFSTimer() == 0 && (*it)->getBackOffTime() == 0) {
            readyToTransmit.push_back(*it);
        }
    }
    return readyToTransmit;

}

void Simulation::startTrans(){
    list<Station*> readyToTransmit;
    list<Station*>::iterator it;
    list<Station*> temp = getStations();
    
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getrdyToTransmit() == true && (*it)->getDIFSTimer() == 0 && (*it)->getBackOffTime() == 0) {
            LineBusy = true;
            (*it)->setStationTransmitting(true);
        }
    }
    AckCounter = ACK_RTS_CTS;
    SIFSCounter = SIFS_duration;
    
    return;
}

void Simulation::incPacketsThrough(){
    list<Station*> stationsTransmiting;
    list<Station*>::iterator it;
    list<Station*> temp = getStations();
    
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getStationTransmitting()) {
            if ((*it)->getPacketsThrough() < 99) {
                (*it)->incPacketsthrough();
            }
            else{
                (*it)->setSentPackets(true);
            }
        }
    }
    
    return;
}

bool Simulation::checkPacketsthrough(){
    list<Station*> stationsTransmiting;
    list<Station*>::iterator it;
    list<Station*> temp = getStations();
    for (it = temp.begin(); it != temp.end(); ++it){
    if ((*it)->getSentPackets()) {
        return true;
    }
}
    return false;
}


void Simulation::deincAck(){
    AckCounter--;
}
void Simulation::deincSIFS(){
    SIFSCounter--;
}

void Simulation::resetNode(){
    list<Station*> stationsTransmiting;
    list<Station*>::iterator it;
    list<Station*> temp = getStations();
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getSentPackets()) {
            (*it)->reset(getGlobalClk());
        }
        else if ((*it)->getrdyToTransmit()){
            (*it)->setDIFSTimer(DIFS_duration);
        }
    }
}
