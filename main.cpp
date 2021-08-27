//Cancel reservation
//- Ask if the user wants to cancel the whole reservation.
//- Make the rooms available again.
// I am assuming he check out as he cancel
// since i saving the guest paid before money
// no ones leave without pay :), i prefer to call it checkOut
#include <iostream>
#include <vector>
#include <string>
#include "Account.h"
#include "Room.h"
#include <list>

#define humanClass "Human"
#define monsterClass "Monster"
#define option1 "roomOption"
#define option2 "dryCleanOption"
#define option3 "spaOption"
using namespace std;

vector<Room> initRooms(){
    //room numbers are they room indices
    vector<Room> Rooms;
    for(int i=0;i<5;i++){
        Rooms.emplace_back(Room(i, humanClass));
    }
    for(int i=5;i<20;i++){
        Rooms.emplace_back(Room(i, monsterClass ));
    }
    return Rooms;
}
Account createAcc(int accountsLen){
    //create guest account
    int baseID = 777;
    string name; cout << "what is ur name?" <<endl; cin >> name;
    string type = humanClass;
    int isMonster; cout <<"Are you Monster?" << endl; cin >>isMonster;
    if(isMonster==1){
        type = monsterClass;
    }
    Account account(accountsLen+baseID, name, type);
    cout << "Use this id next time\n" << account.getID() << endl;
    return account;
}
int findAcc(vector<Account> Accounts){
    int  id; cout << "what is ur id?" <<endl; cin >> id;
    //search for guest account
    for(int i=0; i<Accounts.size(); i++){
        if(Accounts[i].getID() == id){
            return i;
        }
    }
    return -1;
}
int findRoom(Account account,vector<Room> Rooms){
    for(int i=0; i<Rooms.size(); i++){
        if(Rooms[i].isFree() && Rooms[i].roomClass()==account.getClass() ){
            return i;
        }
    }
    return -1;
//    throw "there is no available room";
}
double costOf(string type, string option){
    if(type==monsterClass){
        if(option==option1){
            return 200;
        }
        else if(option==option2){
            return 30;
        }
        else //if(option==option3)
        {
            return 50;
        }
    }else{
        if(option==option1){
            return 500;
        }
        else if(option==option2){
            return 70;
        }
        else //if(option==option3)
        {
            return 100;
        }
    }
}

int main()
{

    //init
    vector<Room> Rooms = initRooms();
    vector<Account> Accounts;

    bool loop = true;
    while(loop)
    {
        //get guest account

        int guest_index;//NOT THE ID,  index in the database vector

        cout << "Welcome to our suit hotel..." << endl;
        cout << "is this ur first time to visit?\n1 for Yes\t0 for No" << endl;
        int firstTime; cin >> firstTime;
        if (firstTime == 1)
        {
            Accounts.emplace_back(createAcc(Accounts.size()));
            guest_index = Accounts.size()-1;
        } else{
            do {
                guest_index = findAcc(Accounts);
                if (guest_index == -1) {
                    cout << "account doesn't exist" << endl;
                    cout << "do u want to create one?\n1:create account \t0:no,re-enter it" << endl;
                    int create = 0;
                    cin >> create;
                    if (create == 1) {
                        Accounts.emplace_back(createAcc(Accounts.size()));
                        guest_index = Accounts.size() - 1;
                    }
                }
            }while (guest_index == -1);
        }



        //serve the guest
        cout << "here what could i do for you, if u want:" << endl;
        cout << "1: New Reservation\n2: Extend Reservation\n3: Cancel Reservation\n4: Additional Services\n"
                "5: next guest\nelse: end program" << endl;
        int i; cin >> i;
        switch (i)
        {
            case 1:{

                int room_index;
                //number of nights
                cout << "Enter the number of nights" << endl;
                int nights; cin >> nights;
                //number of rooms
                cout << "How many rooms you want?" << endl;
                int nRooms; cin >> nRooms;
                double costPerNight = costOf(Accounts[guest_index].getClass(), option1);
                double costPerRoom = costPerNight * nights;
                for(int i=0; i<nRooms; i++) {
                    //find a room
                    room_index = findRoom(Accounts[guest_index], Rooms);
                    if (room_index != -1) {
                        //book room
                        Rooms[room_index].reserve(Accounts[guest_index].getID(), nights);
                        //assign room & it's cost to the guest
                        Accounts[guest_index].assignRoomN(room_index, costPerRoom);//room numbers is room indices from initRooms()
                        cout << "Room#"<< room_index << endl;
                    }else{
                        cout << "No more available rooms, sorry." << endl;
                        break;
                    }
                }
                cout << "Your Total Cost: " << Accounts[guest_index].getCostToPay() << endl;
                break;
            }
            case 2:{
                //number of nights
                int nights;
                cout << "Enter the number of nights" << endl;
                cin >> nights;

                //room numbers is room indices
                vector<int> roomsNumbers = Accounts[guest_index].getRoomsNumbers(); //his rooms

                if(roomsNumbers.size()!=0){
                    for(int roomNumber : roomsNumbers){
                        Rooms[roomNumber].extend(nights);
                    }
                }else{
                    cout << "Sir, rserve room(s) first..." << endl;
                }
                double costPerNight = costOf(Accounts[guest_index].getClass(), option1);
                double totalCost = Accounts[guest_index].addCost(roomsNumbers.size()*nights*costPerNight);
                cout << "Your Total Cost: " << totalCost << endl;
                break;
            }
            case 3:{
                //room numbers is room indices
                vector<int> roomsNumbers = Accounts[guest_index].getRoomsNumbers(); //his rooms
                for(int roomNumber : roomsNumbers){
                    Rooms[roomNumber].freeRoom();
                }
                double totalPaid = Accounts[guest_index].checkOut();
                Accounts[guest_index].unlinkRooms();
                cout << "Your Total Paid: " << totalPaid << endl;

                break;
            }
            case 4:{
                double costOfService;

                cout << "2: Dry Clean\telse: Spa" << endl;
                int dc; cin >> dc;
                if(dc==2){
                    costOfService = costOf(Accounts[guest_index].getClass(), option2);
                }else{
                    costOfService = costOf(Accounts[guest_index].getClass(), option3);
                }
                double totalCost = Accounts[guest_index].addCost(costOfService);
                cout << "Your Total Cost: " << totalCost << endl;
                break;
            }
            case 5:
                continue;
            default:
                loop = false;
                //loop for the next guest
        }

    }
    return 0;
}



