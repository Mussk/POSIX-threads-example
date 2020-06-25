//
// Created by Alexandr Karpenko on 4/14/20.
//

#ifndef ZSO1_SOFASERVICE_H
#define ZSO1_SOFASERVICE_H


#include "ThreadManager.h"



class SofaService {

public:
    pthread_t run_thread_wr_sofa();
    static void* tread_worker_wr_sf(void* args);

};

#endif //ZSO1_SOFASERVICE_H
