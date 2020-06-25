//
// Created by Alexandr Karpenko on 4/16/20.
//




#include <iostream>
#include <thread>
#include "HairdresserService.h"
#include "Sofa.h"
#include "Hairdresser.h"

#include "Kasa.h"
#include "Waiting_Room.h"
#include "Delay.h"


pthread_cond_t hd_sf_cv = PTHREAD_COND_INITIALIZER;//sofa-hairdresser
pthread_cond_t hd_ks_cv = PTHREAD_COND_INITIALIZER;//kasa-hairdresser
pthread_mutex_t hd_mutex = PTHREAD_MUTEX_INITIALIZER;
std::string hd = "[Hairdresser ";

void* HairdresserService::thread_worker_hd(void *id) {

    Hairdresser *hairdresser = new Hairdresser((long)id);

    Waiting_Room *waiting_room = Waiting_Room::getInstance();

    Sofa *sofa = Sofa::getInstance();

    Kasa* kasa = Kasa::getInstance();

    std::cout << hd << hairdresser->getId() << "] Hairdresser starts waiting" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

    pthread_cond_wait(&hd_sf_cv,&hd_mutex);

    std::cout << hd << hairdresser->getId() << "] Hairdresser awakes..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

    //taking client from sofa

    while(sofa->getPoolSize() > 0L) {

        hairdresser->setClient(sofa->getClient());



        pthread_mutex_unlock(&hd_mutex);

        hairdresser->make_haircut();

        //move client to kasa
        kasa->setClient(hairdresser->getClient());
        hairdresser->removeClient();
        //signal to kasa
        pthread_cond_signal(&hd_ks_cv);
        //kasa do some work
        std::cout << hd << " " << id << "] Waiting signal from kassa" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
        pthread_cond_wait(&hd_ks_cv,&hd_mutex);

        if (sofa->getPoolSize() == 0L && waiting_room->getPoolSize() == 0L) {

            std::cout << hd << " "<< id  << "] No clients left, terminating..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

            pthread_mutex_unlock(&hd_mutex);

            pthread_mutex_destroy(&hd_mutex);

            pthread_exit(0);

        }
        //notify sofa to add new client
        pthread_cond_signal(&hd_sf_cv);
        std::cout << hd << hairdresser->getId() << "] Waiting for signal from sofa..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
        //waiting for signal from sofa
        pthread_cond_wait(&hd_sf_cv,&hd_mutex);

        std::cout << hd << hairdresser->getId() << "] Recieved signal from sofa, taking new client" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

    }

    std::cout << hd << hairdresser->getId() << "] There are no clients more, terminating..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

    pthread_exit(0);
}


pthread_t* HairdresserService::run_threads() {

    pthread_t hd_threads[Hairdresser::HD_MAX_ID];


    for (long i = 0L; i < Hairdresser::HD_MAX_ID; ++i) {

        pthread_create(&hd_threads[i],NULL,HairdresserService::thread_worker_hd,(void *) i);
        
    }

    return hd_threads;

}

