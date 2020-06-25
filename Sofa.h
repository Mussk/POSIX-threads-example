//
// Created by Alexandr Karpenko on 3/11/20.
//

#ifndef ZSO1_SOFA_H
#define ZSO1_SOFA_H

#include "Client.h"
#include <list>

extern std::string sf;

class Sofa {
private:
    std::list<Client*> clients_sofa;

    static Sofa* instance;
    Sofa() {}

public:
    static unsigned long const MAX_PEOPLE_SOFA = 4L;
    static Sofa* getInstance();
    Client* getClient();
    unsigned long getPoolSize();
    void returnClient(Client* object);


};
#endif //ZSO1_SOFA_H
