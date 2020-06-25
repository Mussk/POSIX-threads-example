//
// Created by Alexandr Karpenko on 4/13/20.
//

#include <iostream>
#include <list>
#include "Client.h"
#include "Waiting_Room.h"

/* Note, that this class is a singleton. */
//This is pool of clients of Waiting Room

    /**
     * Static method for accessing class instance.
     * Part of Singleton design pattern.
     *
     * @return ClientPool instance.
     */
    Waiting_Room* Waiting_Room::getInstance()
    {
        if (instance == 0)
        {
            instance = new Waiting_Room;
        }
        return instance;
    }
    /**
     * Returns instance of Client.
     *
     * New Client will be created if all the clients
     * were used at the time of the request.
     *
     * @return Client instance.
     */
    Client* Waiting_Room::getClient()
    {
        if (clients.empty())
        {

            return new Client();
        }
        else
        {

            Client* Client = clients.front();
            clients.pop_front();
            return Client;
        }
    }

    unsigned long Waiting_Room::getPoolSize(){

        return clients.size();
    }
    /**
     * Return Client back to the pool.
     *
     * The Client must be initialized back to
     * the default settings before someone else
     * attempts to use it.
     *
     * @param object Client instance.
     * @return void
     */
    void Waiting_Room::returnClient(Client* object)
    {
        object->reset();
        clients.push_back(object);
    }

Waiting_Room* Waiting_Room::instance = 0;


