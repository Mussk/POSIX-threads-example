cmake_minimum_required(VERSION 3.9)
project(ZSO1)

find_library(PTHREAD_LIBRARY pthread)

set(CMAKE_CXX_STANDARD 17)

add_executable(ZSO1 main.cpp Generator.cpp Generator.h Sofa.cpp Sofa.h Client.cpp Client.h Waiting_Room.cpp Waiting_RoomService.cpp Waiting_RoomService.h Waiting_Room.h SofaService.cpp SofaService.h ThreadManager.h Hairdresser.cpp Hairdresser.h HairdresserService.cpp HairdresserService.h Kasa.cpp Kasa.h KasaService.cpp KasaService.h Delay.h)

target_link_libraries(ZSO1 ${PTHREAD_LIBRARY})