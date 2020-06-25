

#ifndef ZSO1_GENERATOR_H
#define ZSO1_GENERATOR_H



#include "Client.h"
#include <list>
#define DELAY = 2000;
//class with list of people who waits in street
class Generator {

private:
    std::list<Client*> clients_street;
    static Generator* instance;
    Generator() {

        generate_clients(CLIENTS_COUNT);
    }

public:
    static Generator* getInstance();
    static const int CLIENTS_COUNT = 50;
    void generate_clients(int count);
    std::list<Client *> &getClients_street();


};


#endif //ZSO1_GENERATOR_H
