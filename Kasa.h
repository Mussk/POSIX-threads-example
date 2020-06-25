//
// Created by Alexandr Karpenko on 4/18/20.
//

#ifndef ZSO1_KASA_H
#define ZSO1_KASA_H

#include <list>
#include "Client.h"

extern std::string ks;

class Kasa{
private:
    Client* client;
    int count = 0;
    static Kasa* instance;
    Kasa() {}

public:

    static Kasa* getInstance();
    void setClient(Client *client);

    Client *getClient();

    void pay();

    void removeClient();

};

#endif //ZSO1_KASA_H
