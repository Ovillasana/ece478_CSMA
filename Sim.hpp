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
#include <iostream>
#include "Station_Creation.hpp"

class Simulation {
    int globalClock = 0;
    list<Station*> stations;
    bool transCompl = false;
    bool LineBusy  = false;
    bool nodeToTransmit = false;
    int collisionCounter = 0;
    int time_in_Sec = 0;  // used to claculate the throughput
    int DIFS_duration = 2; //40us
    int slotDuration = 20; //20us
    int dataFrameSize = 1500; //1500 bytes
    int SIFS_duration = 1; //10us made this up
    int ACK_RTS_CTS = 2; // 30 bytes // made this up
    int transmissionRate = 6; // 6Mbps
    int simulationTime = 10; //10sec
    int transmissionTime = 100; //made this up for test
    int lowestBackoffTimer = 0; //lowest back off timer between the nodes
    int kColisionCounter = 1;
    int SIFSCounter = 0;
    int AckCounter = 0;
    bool RTSCTS = false;
    bool collisionBool = false;
    vector<string> status{"Trans","Receiving","DIFS","RTS","CTS","NAVRTS","NAVCTS","BackOff","SIFS","Freeze","ACK","Idle","Wait"};

    
public:
    int getGlobalClk(){return globalClock;};
    void incGlobalClk(int inc){globalClock+=inc;}; // incriments global clock by amount
    bool checkifLineIsBusy(){return LineBusy;};
    void incCollisionCounter(int inc){collisionCounter+=inc; return;};
    void setStations(list<Station*> newstations){stations = newstations;return;}
    list<Station*> getStations(){return stations;};
    void setLineBusy(){LineBusy = true; return;};
    void setLineNotBusy(){LineBusy = false; return;};
    int getDIFS(){return DIFS_duration;}
    int getTranTime(){return transmissionTime;}
    int getSIFS(){return SIFS_duration;}
    int getACK(){return ACK_RTS_CTS;}
    bool senseDIFS();
    void deincrimentBackoffTime();
    int getLowestBackoff(){return lowestBackoffTimer;}
    void setLowestBackoff(int time){lowestBackoffTimer = time; return;};
    void senseLowestBackOffTime();
    void deincrimentCounters();
    bool getNodewaiting(){return nodeToTransmit;}
    void setNodewaiting(bool value){nodeToTransmit = value;}
    list<Station*> checkForStationsReadytoTrans();
    void startTrans();
    void incPacketsThrough();
    bool checkPacketsthrough();
    int getSIFSCounter(){return SIFSCounter;}
    void setSIFSCounter(){SIFSCounter = SIFS_duration;}
    int getAckCounter(){return AckCounter;}
    void setAckCounter(){AckCounter = ACK_RTS_CTS;}
    void deincAck();
    void deincSIFS();
    void resetNode();
    int getcollisioncounter(){return collisionCounter;}
    void resetK(){kColisionCounter = 1;}
    int getK(){return kColisionCounter;}
    void incrK(){kColisionCounter++;}
    void sendRTS();
    list<Station*> StationsthatareTrans();
    void setRTSCTS(){RTSCTS = true;}
    bool getRTSCTS(){return RTSCTS;}
    void deincRTS();
    void deincCTS();
    string getStatusat(int val){return status.at(val);}
    void updateStatus();
    void conectionsRec();
    void collisionCheck();
    

};

#endif /* Sim_hpp */
