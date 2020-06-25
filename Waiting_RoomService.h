//
// Created by Alexandr Karpenko on 4/13/20.
//

#ifndef ZSO1_WAITING_ROOMSERVICE_H
#define ZSO1_WAITING_ROOMSERVICE_H

#include "ThreadManager.h"




class Waiting_RoomService {

public:
    pthread_t run_thread_wr_st();
    static void* thread_worker_wr_st(void *arguments);

};

#endif //ZSO1_WAITING_ROOMSERVICE_H
