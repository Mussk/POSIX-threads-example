//
// Created by Alexandr Karpenko on 4/16/20.
//

#ifndef ZSO1_HAIRDRESSERSERVICE_H
#define ZSO1_HAIRDRESSERSERVICE_H

#include <sys/_pthread/_pthread_t.h>



class HairdresserService {


public:
    static void* thread_worker_hd(void* id);
    pthread_t *run_threads();
};


#endif //ZSO1_HAIRDRESSERSERVICE_H
