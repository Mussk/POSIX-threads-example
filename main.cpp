

#include <chrono>
#include <thread>
#include "Waiting_RoomService.h"
#include "SofaService.h"
#include "HairdresserService.h"
#include "KasaService.h"



int main() {


    KasaService* kasaService = new KasaService;

    pthread_t ks_thread = kasaService->run_thread_hd_ks();

    HairdresserService* hairdresserService = new HairdresserService;

    pthread_t *hd_service_threads = hairdresserService->run_threads();

    SofaService* sofaService = new SofaService;

    pthread_t sf_wr_thread = sofaService->run_thread_wr_sofa();

    Waiting_RoomService* waiting_roomService = new Waiting_RoomService;

    pthread_t wr_st_thread = waiting_roomService->run_thread_wr_st();

    pthread_join(wr_st_thread,NULL);
    pthread_join(sf_wr_thread,NULL);
    pthread_join(*hd_service_threads,NULL);
    pthread_join(ks_thread,NULL);


    return 0;
}