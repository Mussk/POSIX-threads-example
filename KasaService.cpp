//
// Created by Alexandr Karpenko on 4/18/20.
//

#include <iostream>
#include <thread>
#include "KasaService.h"
#include "Hairdresser.h"
#include "Kasa.h"
#include "Delay.h"


std::string ks = "[Kasa] ";

void* KasaService::thread_worker_hd_ks(void *arguments) {

    Kasa* kasa = Kasa::getInstance();

    pthread_mutex_t kasa_mutex = PTHREAD_MUTEX_INITIALIZER;

    std::cout << ks << "Kasa thread started" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

    std::cout << ks << "Kasa thread start waiting..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

    while(1) {

        pthread_cond_wait(&hd_ks_cv, &kasa_mutex);
        //move client from hairdresser to kasa
        std::cout << ks << "Kasa awakes..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(Delay));

        if (kasa->getClient() != NULL) {

            kasa->pay();

            kasa->removeClient();

        }

        pthread_mutex_unlock(&kasa_mutex);
        std::cout << ks << "Awaking hairdresser..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
        //awake hairdresser
        pthread_cond_signal(&hd_ks_cv);

    }
}

pthread_t KasaService::run_thread_hd_ks() {

    pthread_t ks_thread;

    pthread_create(&ks_thread,NULL,KasaService::thread_worker_hd_ks,NULL);

    return ks_thread;
}