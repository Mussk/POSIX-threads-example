//
// Created by Alexandr Karpenko on 3/11/20.
//

#include <iostream>
#include "Sofa.h"


Sofa* Sofa::getInstance()
{
    if (instance == 0)
    {
        instance = new Sofa;
    }
    return instance;
}

Client* Sofa::getClient()
{
    if (clients_sofa.empty())
    {

        return new Client();
    }
    else
    {
        Client* Client = clients_sofa.front();
        clients_sofa.pop_front();
        return Client;
    }
}

unsigned long Sofa::getPoolSize(){

    return clients_sofa.size();
}

void Sofa::returnClient(Client* object)
{
    object->reset();
    clients_sofa.push_back(object);
}

Sofa* Sofa::instance = 0;

