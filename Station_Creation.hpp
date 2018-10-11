//
//  Station_Creation.hpp
//  Proj_1
//
//  Created by Alec Foster on Thursday10/4.
//  Copyright © 2018 Alec Foster. All rights reserved.
//

#ifndef Station_Creation_hpp
#define Station_Creation_hpp

#include <string.h>
#include <stdio.h>
#include <string>
#include <list>
#include <vector>

using namespace std;


class Station {
    char stationName = '_';
    list<Station*> connections;
    int lambda = 0;
    list<Station*> inRange;
    list<int> slot_List{};
    int packetsThrough = 0;
    int CW_0 = 4; //4 slots
    int CW_max = 1024; //1024 slots
    bool readyToTransmit = false;
    bool stationTransmitting = false;
    bool sentPackets = false;
    int back_off_timer = 0;
    vector<double> slot_List_vec;
    int DIFS_timer = 0;
    int transmisionsThrough = 0;
    int kCounter = 1;

    
public:
    void station_Create (char name);
    void in_range_Create(Station* new_Station);
    void set_Lambda(int num);
    void connection_Create(Station* new_Station);
    void add_Slot_to_List(int newSlot);
    void randBackOffTime();
    int getSlotList(){return slot_List.front();};
    
    void setrdyToTrans(){readyToTransmit = true; return;};
    void setnotrdyToTrans(){readyToTransmit = false; return;}
    bool getrdyToTransmit(){return readyToTransmit;}
    void popList(){slot_List.pop_front();return;}
    void sort_list(){slot_List.sort(); return;}
    int getBackOffTime(){return back_off_timer;};
    void subtBackOffTime(){back_off_timer--; return;}
    void doubleContention(int k);
    vector<double>& getpointSlotList(){return slot_List_vec;}
    void makeList();
    int getDIFSTimer(){return DIFS_timer;}
    void setDIFSTimer(int time){DIFS_timer = time;}
    void subtDIFSTimer(){DIFS_timer--;}
    void setStationTransmitting(bool val){stationTransmitting = val;}
    bool getStationTransmitting(){return stationTransmitting;}
    void incPacketsthrough(){packetsThrough++;}
    void resetPacketsThrough(){packetsThrough = 0;}
    int getPacketsThrough(){return packetsThrough;}
    void setSentPackets(bool val){sentPackets = val;}
    bool getSentPackets(){return sentPackets;}
    void reset(int time);
    void incTransmisionsThrough(){transmisionsThrough++;}
    int getTransmissionsThrough(){return transmisionsThrough;}
    int getK(){return kCounter;}
    void incrK(){kCounter++;}
    void resetK(){kCounter =1;}

    
};

#endif /* Station_Creation_hpp */
