//
// Created by Alexandr Karpenko on 4/13/20.
//

#ifndef ZSO1_WAITING_ROOM_H
#define ZSO1_WAITING_ROOM_H

#include <list>
#include "Client.h"

extern std::string wr;

class Waiting_Room{
private:
    std::list<Client*> clients;

    static Waiting_Room* instance;
    Waiting_Room() {}

public:
    static unsigned long const MAX_PEOPLE_WR = 16L;
    static Waiting_Room* getInstance();
    Client* getClient();
    unsigned long getPoolSize();
    void returnClient(Client* object);


};
#endif //ZSO1_WAITING_ROOM_H
