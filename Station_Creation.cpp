//
//  Station_Creation.cpp
//  Proj_1
//
//  Created by Alec Foster on Thursday10/4.
//  Copyright © 2018 Alec Foster. All rights reserved.
//

#include "Station_Creation.hpp"
#include "Sim.hpp"
#include <math.h>


void Station::station_Create(char name){ // creates station name
    stationName = name;
    return;
}

void Station::in_range_Create(Station* new_Station){ // creates a list of stations the current station is in range of
    inRange.push_back(new_Station);
    return;
}

void Station::set_Lambda(int num){ // Sets lambda for each station
    lambda = num;
    return;
}

void Station::connection_Create(Station* new_Station){ // creates a list of the stations that the current station is transmitting trying to transmit to
    connections.push_back(new_Station);
    return;
}

void Station::add_Slot_to_List(int newSlot){ // adds a new slot number to the list for node
    slot_List.push_front(newSlot);
    return;
}

void Station::randBackOffTime(){
    back_off_timer = (rand() % (CW_0 - 0)) + 1;
    
    return;
}

void Station::doubleContention(int k){
    int newK = pow(2.0, k);
    back_off_timer = (rand() % (newK * CW_0 - 0)) + 1;
    return;
}

void Station::makeList(){
    // list.assign(vector.begin(), vector.end());
    slot_List.assign(slot_List_vec.begin(), slot_List_vec.end());
    return;
}

void Station::reset(int time){
    transmisionsThrough++;
    packetsThrough = 0;
    readyToTransmit = false;
    stationTransmitting = false;
    sentPackets = 0;
    for (int i = 0; i < slot_List.size(); i++) {
        if (slot_List.front()<time) {
            slot_List.pop_front();
        }
    }
}








