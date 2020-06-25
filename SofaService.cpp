//
// Created by Alexandr Karpenko on 4/14/20.
//


#include <iostream>
#include <thread>
#include "SofaService.h"
#include "Waiting_Room.h"
#include "Sofa.h"
#include "Hairdresser.h"
#include "Delay.h"


pthread_cond_t wr_sf_cv = PTHREAD_COND_INITIALIZER;

std::string sf = "[Sofa]";

void* SofaService::tread_worker_wr_sf(void *args) {

pthread_mutex_t sofa_mutex = PTHREAD_MUTEX_INITIALIZER;

    //may produce concurrent problems with waiting room service thread
    Waiting_Room *waiting_room = Waiting_Room::getInstance();

    Sofa *sofa = Sofa::getInstance();

    std::cout << sf << "Sofa starts waiting" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

    pthread_cond_wait(&wr_sf_cv,&sofa_mutex);

    std::cout << sf << "sofa Was awakened" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

    while(sofa->getPoolSize() < Sofa::MAX_PEOPLE_SOFA) {

                            //returns clients.front()
        sofa->returnClient(waiting_room->getClient());

        std::cout << sf << "client was moved on sofa" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
        if(sofa->getPoolSize() == Sofa::MAX_PEOPLE_SOFA ||
                waiting_room->getPoolSize() == 0L) {

            std::cout << sf << "Reached max size of sofa: " << std::endl;
            std:: cout << sofa->getPoolSize() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
            std::cout << sf << "Send signal to hairdresser" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
            //notify of hairdresser
            pthread_cond_signal(&hd_sf_cv);
            pthread_mutex_unlock(&sofa_mutex);

            std::cout << sf << "waiting when hairdresser takes client" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
            pthread_cond_wait(&hd_sf_cv, &hd_mutex);
            //nofity waiting room
            int sg = pthread_cond_signal(&wr_sf_cv);
            if (sg == 0) std::cout << sf << "Successfully notified wr thread" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
            if (waiting_room->getPoolSize() == 0L) {

                std::cout << sf << "No clients left, terminating..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

                pthread_mutex_unlock(&sofa_mutex);

                pthread_mutex_destroy(&sofa_mutex);

                pthread_exit(0);

            }
            //releases lock
            pthread_cond_wait(&wr_sf_cv, &sofa_mutex);
            //got notify from inner thread
            //locks mutex
        }
    }



    pthread_mutex_unlock(&sofa_mutex);

    std::cout << sf << "Mutex unlocked sofa" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

    pthread_exit(NULL);

    return NULL;
}

pthread_t SofaService::run_thread_wr_sofa() {

    pthread_t wr_sf_thread;

    std::cout << sf << "Starting sofa thread" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

    int rc = pthread_create(&wr_sf_thread, NULL, SofaService::tread_worker_wr_sf, NULL);

    if(rc) { std::cout << sf << "error" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(Delay));}

    return wr_sf_thread;
}