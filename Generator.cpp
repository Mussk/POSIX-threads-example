#include "Generator.h"


Generator* Generator::getInstance()
{
    if (instance == 0)
    {
        instance = new Generator;
    }
    return instance;
}

//fullfill list of client what are coming from street
void Generator::generate_clients(int count) {

    for (int i = 0; i < count; ++i) {

        clients_street.push_back(new Client());
    }

    }

std::list<Client *> &Generator::getClients_street() {
    return clients_street;
}

Generator* Generator::instance = 0;



