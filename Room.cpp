//
// Created by amosa on 8/26/2021.
//

#include "Room.h"
#include <exception>
using namespace std;
Room::Room(int number, string roomType) {
    this->roomNumber = number; //constant room number
    this->roomFor =  roomType;
    this->freeRoom();

}
void Room::reserve(int id, int nights) {
    if (this->isFree() == true){
        this->booked = true;
        this->guest_id = id;
        this->nights = nights;
    }
    else{
        throw "Exception: Room not Empty";
    }

}
void Room::extend(int nights) {
    if (this->isFree() == false){
        this->nights += nights;
    }
    else{
        throw "Exception: Must book first";
    }
}
void Room::freeRoom() {
    //free whatever it's free or not
    this->booked = false;
    this->guest_id = -1;
    this->nights = 0;

}
bool Room::isFree() {
    return !this->booked;
}
int Room::getRoomUser() {
    return this->guest_id;
}
int Room::getRoomN() {
    return this->roomNumber;
}
string Room::roomClass() {
    return this->roomFor;
}