//
//  Sim.hpp
//  Proj_1
//
//  Created by Alec Foster on Friday10/5.
//  Copyright © 2018 Alec Foster. All rights reserved.
//

#ifndef Sim_hpp
#define Sim_hpp

#include <stdio.h>
#include "Station_Creation.hpp"

class Simulation {
    int globalClock = 0;
    list<Station*> stations;
    bool transCompl = false;
    bool lineBusy  = false;
    int collisionCounter = 0;
    int time_in_Sec = 0;  // used to claculate the throughput
    int DIFS_duration = 2; //40us
    int slotDuration = 20; //20us
    int dataFrameSize = 1500; //1500 bytes
    int SIFS_duration = 1; //10us made this up
    int ACK_RTS_CTS = 3; // 30 bytes // made this up
    int transmissionRate = 6; // 6Mbps
    int simulationTime = 10; //10sec
    int transmissionTime = 100; //made this up for test
public:
    int getGlobalClk(){return globalClock;};
    void incGlobalClk(int inc){globalClock+=inc;}; // incriments global clock by amount
    bool getLineStatus(){return lineBusy;};
    void setCollisionCounter(int inc){collisionCounter+=inc; return;};
    void setStations(list<Station*> newstations){stations = newstations;return;}
    list<Station*> getStations(){return stations;};
    void setLineBusy(){lineBusy = true; return;};
    void setLineNotBusy(){lineBusy = false; return;};
    int getDIFS(){return DIFS_duration;}
    int getTranTime(){return transmissionTime;}
    int getSIFS(){return SIFS_duration;}
    int getACK(){return ACK_RTS_CTS;}

};

#endif /* Sim_hpp */
