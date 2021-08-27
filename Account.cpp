//
// Created by amosa on 8/26/2021.
//

#include "Account.h"
Account::Account(int id, string userName, string type){
    this->id = id;
    this->userName = userName;
    this->type = type; //class
    this->paid_before = 0;
    this->to_pay = 0; //total cost
}
string Account::getClass() {
    return this->type;

}
double  Account::getCostToPay() {
    return this->to_pay;
}
double Account::assignRoomN(int n, double cost) {
    this->roomsNumbers.emplace_back(n);
    this->to_pay += cost;
    return this->to_pay;
}
vector<int> Account::getRoomsNumbers(){
    return this->roomsNumbers;
}
double Account::addCost(double cost){
    this->to_pay += cost;
    return this->to_pay;
}
int Account::getID() {
    return this->id;
}
double Account::checkOut() {
    this->paid_before += this->to_pay;
    this->to_pay = 0;
    return this->paid_before;
}
void Account::unlinkRooms(){
    this->roomsNumbers.clear();
}