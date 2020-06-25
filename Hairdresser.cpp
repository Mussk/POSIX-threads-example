//
// Created by Alexandr Karpenko on 4/16/20.
//

#include <iostream>
#include <thread>
#include "Hairdresser.h"
#include "Delay.h"


Hairdresser::Hairdresser(long id) {
    setId(id);
}

void Hairdresser::make_haircut() {

    std::cout << hd << " " << id << "] Making a haircut..."<< std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

    std::this_thread::sleep_for(std::chrono::milliseconds(5 + rand()%10));

    std::cout << hd << " " << id << "] Haircut done: " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

}

void Hairdresser::setClient(Client *client) {
    Hairdresser::client = nullptr;
    Hairdresser::client = client;
}

void Hairdresser::setId(long id) {
    Hairdresser::id = id;
}

long Hairdresser::getId() {
    return id;
}

Client *Hairdresser::getClient(){
    return client;
}

void Hairdresser::removeClient(){

    client = NULL;
}
