//
// Created by amosa on 8/26/2021.
//

#ifndef HOTEL_ACCOUNT_H
#define HOTEL_ACCOUNT_H
#include <string>
#include <vector>
using namespace std;

class Account {
private:

    int id;
    string userName;
    string type; //class
    double paid_before;
    double to_pay; //total cost
    vector<int> roomsNumbers;
public:
    Account(int id, string userName, string type);
    double getCostToPay();
    double assignRoomN(int n, double cost);
    string getClass();
    int getID();
    vector<int> getRoomsNumbers();
    double addCost(double cost);
    double checkOut();
    void unlinkRooms();
};


#endif //HOTEL_ACCOUNT_H
