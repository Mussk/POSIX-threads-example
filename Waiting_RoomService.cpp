//
// Created by Alexandr Karpenko on 4/13/20.
//

/*This class represents a thread which
 * works with people in the street and waiting room */


#include <iostream>
#include <thread>
#include "Waiting_Room.h"
#include "Generator.h"
#include "Waiting_RoomService.h"
#include "Delay.h"

//function what we are locate in thread
//args: list_clients_from_streets, poolWaitingRoom




std::string wr = "[Waiting Room] ";

void* Waiting_RoomService::thread_worker_wr_st(void *arguments) {

    pthread_mutex_t wr_mutex = PTHREAD_MUTEX_INITIALIZER;

    Generator *generator = Generator::getInstance();

    Waiting_Room *waiting_room = Waiting_Room::getInstance();

    std::cout << wr << "locking mutex wr thread" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
    pthread_mutex_lock(&wr_mutex);

    std::cout << wr << "mutex locked" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
    while (waiting_room->getPoolSize() < Waiting_Room::MAX_PEOPLE_WR) {

        if(!generator->getClients_street().empty()) {

            waiting_room->returnClient(generator->getClients_street().front());

            generator->getClients_street().remove(generator->getClients_street().front());

        }

       // std::cout << waiting_room->getPoolSize() << std::endl;

        std::cout << wr << "Clients street left: "<< generator->getClients_street().size() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

        std::cout << wr << "new client moved to waiting room" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

       if(waiting_room->getPoolSize() == Waiting_Room::MAX_PEOPLE_WR ||
               generator->getClients_street().empty()) {

           std::cout << wr << "Reached max size of wr: " << std::endl;
           std:: cout << wr << waiting_room->getPoolSize() << std::endl;
           std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
           //releases lock

           if(waiting_room->getPoolSize() == 0L){


               std::cout<< wr << "Waiting Room is empty...terminating" << std::endl;
               std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

               pthread_mutex_unlock(&wr_mutex);

               pthread_mutex_destroy(&wr_mutex);

               pthread_exit(0);



           }

           pthread_cond_signal(&wr_sf_cv);
           std::cout << wr << "Sent signal to sofa, start waiting..." << std::endl;
           std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
           pthread_cond_wait(&wr_sf_cv, &wr_mutex);
           //got notify from inner thread
           std::cout << wr << "Got signal from sofa, awakening..." << std:: endl;
           std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
           //locks mutex
       }
    }



    return NULL;
}

    pthread_t Waiting_RoomService::run_thread_wr_st(){

    pthread_t wr_st_thread;

        std::cout << wr << "Starting wr thread" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

    int rc = pthread_create(&wr_st_thread, NULL, Waiting_RoomService::thread_worker_wr_st, NULL);

        if (rc) { std::cout << wr << "error" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(Delay));}

    return  wr_st_thread;
}

