//
// Created by amosa on 8/26/2021.
//

#ifndef HOTEL_ROOM_H
#define HOTEL_ROOM_H
#include <string>
using namespace std;

class Room {
private:
    int roomNumber;
    string roomFor;
    bool booked;
    int guest_id;
    int nights;
public:
    Room(int number, string roomType);
    void reserve(int id, int nights);
    void freeRoom();
    void extend(int nights);
    bool isFree();
    int getRoomUser();
    string roomClass();
    int getRoomN();
};


#endif //HOTEL_ROOM_H
