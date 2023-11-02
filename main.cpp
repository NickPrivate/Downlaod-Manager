#include <iostream>
#include <thread>
#include <semaphore.h>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>

#define num_threads 10
#define concurrent_downloads 6

struct Download_Stats {
    std::string fileName;
    float downloadTime;
    bool downloadStatus;
};


void ThreadHandler(sem_t* semaphore, const std::string& URL, const std::string& fileName, Download_Stats& downloadStats) {

    sem_wait(semaphore);
    std::this_thread::sleep_for(std::chrono::seconds(2));


    downloadStats.downloadStatus = true;
    downloadStats.fileName = fileName;
    downloadStats.downloadTime = 2.0;

    sem_post(semaphore);
}




int main(){

    sem_t semaphore;
    sem_init(&semaphore, 0, concurrent_downloads);

    std::vector<std::string> URL = {
    "www.facebook.com/download",
    "www.roblox.com/download",
    "www.vscode.com/download",
    "www.discord.com/download",
    "www.spotify.com/download", 
    "www.steam.com/download", 
    "www.logitech.com/ghub/download",
    "www.razer.com/download",
    "www.shutter.com/download",
    "www.minecraft.com/download"
     };

    
    std::vector<std::string> fileName = {
    "facebook",
    "roblox",
    "vscode",
    "discord",
    "spotify",
    "steam",
    "logitech",
    "razer",
    "shutter",
    "minecraft"
    };




    return 0;
}