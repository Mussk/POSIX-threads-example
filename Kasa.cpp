//
// Created by Alexandr Karpenko on 4/18/20.
//

#include <iostream>
#include <list>
#include <thread>
#include "Client.h"
#include "Waiting_Room.h"
#include "Kasa.h"
#include "KasaService.h"
#include "Delay.h"
/* Note, that this class is a singleton. */
//This is pool of Kasa


Kasa* Kasa::getInstance()
{
    if (instance == 0)
    {
        instance = new Kasa;
    }
    return instance;
}

void Kasa::setClient(Client *client) {
    Kasa::client = client;
}

Client *Kasa::getClient() {
    return client;
}

void Kasa::pay() {

    std::cout << ks << "Client pays on kassa... " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
    std::cout << ks << "payment succeed... " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
};

void Kasa::removeClient() {

    client = NULL;

    count++;
    std::cout << ks << "Client left... " << count << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));


}

Kasa* Kasa::instance = 0;


