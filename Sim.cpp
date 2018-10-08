//
//  Sim.cpp
//  Proj_1
//
//  Created by Alec Foster on Friday10/5.
//  Copyright © 2018 Alec Foster. All rights reserved.
//

#include "Sim.hpp"

bool Simulation::senseDIFS(){
    if (Simulation::getLineStatus()) {
        return true;
    }
    
    return false;
}

void Simulation::deincrimentBackoffTime(){    // goes through list of stations and deindriments Backofftimer
    list<Station*>::iterator it;
    list<Station*> temp = Simulation::getStations();
    for (it = temp.begin(); it != temp.end(); ++it){
        if ((*it)->getBackOffTime() != 0) {
            (*it)->subtBackOffTime();
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
