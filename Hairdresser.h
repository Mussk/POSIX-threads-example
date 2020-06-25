//
// Created by Alexandr Karpenko on 4/16/20.
//

#ifndef ZSO1_HAIRDRESSER_H
#define ZSO1_HAIRDRESSER_H

#include "Client.h"
#include <pthread.h>

extern pthread_cond_t hd_sf_cv;
extern pthread_mutex_t hd_mutex;
extern pthread_cond_t hd_ks_cv;
extern std::string hd;
class Hairdresser {

    long id;
private:
    Client* client;

public:
    void make_haircut();
    Hairdresser(long id);
    void setClient(Client *client);
    static const unsigned long HD_MAX_ID = 3L;
    void setId(long id);

    long getId();

    Client *getClient();

    void removeClient();

};

#endif //ZSO1_HAIRDRESSER_H
