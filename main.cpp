#include <iostream>
#include <thread>
#include <semaphore.h>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>
#include <curl/curl.h>


#define num_threads 10
#define concurrent_downloads 6

struct Download_Stats {
    std::string fileName;
    float downloadTime;
    bool downloadStatus;
};

size_t PreDownload(void* contents, size_t size, size_t nmemb, std::ofstream* file) {
    size_t total_size = size * nmemb;
    file->write(static_cast<char*>(contents), total_size);
    return total_size;
}


void DownloadFile (const std::string& URL, const std::string& fileName){
    

}

void ThreadHandler(sem_t* semaphore, const std::string& URL, const std::string& fileName, Download_Stats& downloadStats){

    sem_wait(semaphore);

    auto start = std::chrono::system_clock::now();
    DownloadFile(URL,fileName);
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;

    sem_post(semaphore);

}




int main(){

    sem_t semaphore;
    sem_init(&semaphore, 0, concurrent_downloads);

    std::vector<std::string> URL = {"www.facebook.com/download", "www.roblox.com/download", "www.vscode.com/download",
    "www.discord.com/download", "www.spotify.com/download", "www.steam.com/download", "www.logitech.com/ghub/download",
    "www.razer.com/download", "www.shutter.com/download","www.minecraft.com/download"};
    
    std::vector<std::string> fileName = {"facebook", "roblox", "vscode","discord", "spotify", "steam", "logitech", "razer",
    "shutter", "minecraft"};






    return 0;
}