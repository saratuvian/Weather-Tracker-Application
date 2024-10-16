// ConnectedApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include "CommonObject.h"
#include "DrawThread.h"
#include "DownloadThread.h"



int main()
{
    CommonObjects common;//instance of CommonObjects is created.
    DrawThread draw;//instance of DrawThread is created.
    auto draw_th = std::jthread([&] {draw(common); }); //create draw jthread for the drawing task with common 
    DownloadThread down;//instance of DownloadThread is created.
    auto down_th = std::jthread([&] {down(common); });//create download jthread for the downloading task with common
    std::cout << "running...\n"; //indicate running
    down_th.join(); // main thread waiting for dounload thread
    draw_th.join(); // main thread waiting for draw thread
    return 0;

}

