//
//  Station_Creation.cpp
//  Proj_1
//
//  Created by Alec Foster on Thursday10/4.
//  Copyright © 2018 Alec Foster. All rights reserved.
//

#include "Station_Creation.hpp"
#include "Sim.hpp"


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

int Station::backOffTime(){
    int backOff = (rand() % (CW_0 - 0)) + 0;
    return backOff;
}








