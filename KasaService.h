//
// Created by Alexandr Karpenko on 4/18/20.
//

#ifndef ZSO1_KASASERVICE_H
#define ZSO1_KASASERVICE_H

#include "ThreadManager.h"



class KasaService {

public:

    pthread_t run_thread_hd_ks();
    static void* thread_worker_hd_ks(void *arguments);

};

#endif //ZSO1_KASASERVICE_H
