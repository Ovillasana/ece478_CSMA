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
        if ((*it)->getBackOffTime() != 0 && (*it)->getDIFSTimer() == 0 && !(*it)->checkRangeForBusy()) {
            (*it)->subtBackOffTime();
        }
    }
    return;
}

void Simulation::deincrimentCounters(){
    list<Station*>::iterator it;
    list<Station*> temp = Simulation::getStations();
    for (it = temp.begin(); it != temp.end(); ++it){
        //{"Trans","Receiving","DIFS","RTS","CTS","NAVRTS","NAVCTS","BackOff","SIFS","Freeze","ACK","Idle"};
        if ((*it)->getStatusNode() == "DIFS") {
            (*it)->subtDIFSTimer();
        }
        else if ((*it)->getStatusNode() == "RTS") {
            (*it)->deincRTSCounter();
        }
        else if ((*it)->getStatusNode() == "CTS") {
            (*it)->deincCTSCounter();
        }
        else if ((*it)->getStatusNode() == "BackOff") {
            (*it)->subtBackOffTime();
        }
        else if ((*it)->getStatusNode() == "SIFS") {
            (*it)->subSIFS();
        }
        else if ((*it)->getStatusNode() == "Trans") {
            (*it)->subTransmistCounter();
        }
        else if ((*it)->getStatusNode() == "ACK") {
            (*it)->deincACKcounter();
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
            (*it)->setSIFS();
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
    list<Station*> stationsTransmiting;
    list<Station*>::iterator it;
    list<Station*> temp = getStations();
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getSIFS() > 0) {
            (*it)->subSIFS();
        }
    }
}

void Simulation::resetNode(){
    list<Station*> stationsTransmiting;
    list<Station*>::iterator it;
    list<Station*> temp = getStations();
    bool colis = false;
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getSentPackets() && (*it)->getSIFS() ==0 && StationsthatareTrans().size() == 1) {
            (*it)->resetSucsess(getGlobalClk());// reset sucessfull
        }
        else if ((*it)->getSentPackets() && (*it)->getSIFS() ==0 && StationsthatareTrans().size() > 1){
            // reset colision
            (*it)->resetCollision();
            colis = true;
        }
    }
    if (colis) {
        incCollisionCounter(1);
        for (it = temp.begin(); it != temp.end(); ++it){
            (*it)->setStationTransmitting(false);
        }
    }
}

void Simulation::sendRTS(){
        list<Station*>::iterator it;
        list<Station*>::iterator it2;
        list<Station*> temp = Simulation::getStations();
        for (it = temp.begin(); it != temp.end(); ++it){
            if ((*it)->getDIFSTimer() == 0 && (*it)->getrdyToTransmit() && (*it)->getBackOffTime() == 0 && (*it)->getRTSCounter() == 0) {
                list<Station*> temp2 = (*it)->getConections();
                for (it2 = temp2.begin(); it2 != temp2.end(); ++it2) {
                    (*it2)->RTSRec();
                    if ((*it2)->getRTSRec()) {
                        (*it2)->setCTSCounter();
                    }
                }
            }
        }
    return;
}

list<Station*> Simulation::StationsthatareTrans(){
    
    list<Station*> transmitingStations;
    list<Station*>::iterator it;
    list<Station*> temp = getStations();
    
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getStationTransmitting()) {
            transmitingStations.push_back(*it);
        }
    }
    return transmitingStations;
    
}

void Simulation::deincRTS(){
    list<Station*>::iterator it;
    list<Station*> temp = Simulation::getStations();
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getBackOffTime() == 0 && (*it)->getDIFSTimer() == 0 && !(*it)->checkRangeForBusy() && (*it)->getRTSCounter() != 0) {
            (*it)->deincRTSCounter();
        }
    }
    return;
    
}
void Simulation::deincCTS(){
    list<Station*>::iterator it;
    list<Station*> temp = Simulation::getStations();
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getBackOffTime() == 0 && (*it)->getDIFSTimer() == 0 && !(*it)->checkRangeForBusy() && (*it)->getRTSCounter() == 0 && (*it)->getRTSRec()) {
            (*it)->deincCTSCounter();
        }
    }
    return;
    
}

void Simulation::updateStatus(){
    list<Station*>::iterator it;
    list<Station*> temp = Simulation::getStations();
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getStatusNode() == "DIFS") {
            if ((*it)->getDIFSTimer() == 0) {
                (*it)->setStatus("BackOff");
            }
        }
        else if ((*it)->getStatusNode() == "RTS") {
            if ((*it)->getRTSCounter() == 0) {
                (*it)->sendRTS();
                (*it)->setStatus("SIFS");
                (*it)->setSIFS();
                
            }
        }
        else if ((*it)->getStatusNode() == "CTS") {
            if ((*it)->getCTSCounter() == 0) {
                (*it)->setStatus("Idle");
            }
        }
        else if ((*it)->getStatusNode() == "BackOff") {
            if ((*it)->getBackOffTime() == 0) {
                if (!RTSCTS) {
                    (*it)->setStatus("Trans");
                    (*it)->setTransCounter();
                    (*it)->conectionsRec();
                    LineBusy = true;
                }
                else if (RTSCTS){
                    (*it)->setStatus("RTS");
                    (*it)->setRTSCounter();
                    (*it)->conectionsRec();
                }
            }
            else if ((*it)->checkRangeForBusy()){
                (*it)->setStatus("Freeze");
            }
        }
        else if ((*it)->getStatusNode() == "SIFS") {
            if ((*it)->getSIFS() == 0) {
                if (getRTSCTS()) {
                    //FIX ME
                }
                
                if (!(*it)->receiverisACK()) {
                    (*it)->setStatus("Idle");
                    (*it)->doubleContention((*it)->getK());
                    collisionCounter++;
                }
                else if ((*it)->receiverisACK()){
                    (*it)->setStatus("Wait");
                }
            }
        }

        else if ((*it)->getStatusNode() == "Trans") {
            if ((*it)->getTransmitCounter() == 0) {
                collisionCheck();
                if (collisionBool) {
                    (*it)->conectionsIdle();
                    LineBusy = false;
                }
                else{
                    (*it)->conectionsACK();
                }
                (*it)->setStatus("SIFS");
                (*it)->setSIFS();
            }
        }
        else if ((*it)->getStatusNode() == "Freeze") {
            if (!(*it)->checkRangeForBusy()) {
                (*it)->setStatus("Idle");
            }
        }
    
        else if ((*it)->getStatusNode() == "ACK") {
            if ((*it)->getAckCounter() == 0) {
                (*it)->setStatus("Idle");
            }
        }
        else if ((*it)->getStatusNode() == "Wait") {
            if ((*it)->checkAckisDone()) {
                (*it)->setStatus("Idle");
                (*it)->incPacketsthrough();
                (*it)->resetK();
                (*it)->popList(globalClock);
                LineBusy = false;
            }
            else{
                (*it)->setStatus("Wait");
            }
        }
        else if ((*it)->getStatusNode() == "Receiving"){
            if (getRTSCTS()) {
                if ((*it)->getRTSRec()) {
                    (*it)->setStatus("CTS");
                    (*it)->setCTSCounter();
                }
            }
            if ((*it)->getSentPackets()) {
                (*it)->setStatus("Idle");
            }
        }

}
    collisionBool = false;
}

void Simulation::collisionCheck(){
    list<Station*>::iterator it;
    list<Station*> temp = Simulation::getStations();
    int transcollisionCounter = 0;
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getStatusNode() == "Trans") {
            transcollisionCounter++;
        }
    }
    if (transcollisionCounter >1) {
        collisionBool = true;
    }
    
}



