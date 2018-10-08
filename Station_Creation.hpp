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
    int back_off_timer = 0;

    
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

    
};

#endif /* Station_Creation_hpp */
