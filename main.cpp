//Multi Threaded File Download Manger Nov. 2 2023
#include <iostream>
#include <thread>
#include <semaphore.h>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <random>

// setting maximum number of threads and concurrent downloads
const int num_threads = 10;
const int concurrent_downloads = 4;

// struct for holding our download stats
struct Download_Stats {

    std::string fileName;
    std::string URL;
    float downloadTime;
    bool downloadStatus;
    
};

// This function handles the logic for generating download time and giving each download, their respected stats
void ThreadHandler(sem_t* semaphore, const std::string& URL, const std::string& fileName, Download_Stats& downloadStats) {

    // semaphore prevents the threads from executing during each other's critical section
    sem_wait(semaphore);


    // create a random number generator for download times
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> downladTimeTotal(5.0, 15.0);

    // generate a random download time
    float randomDownloadTime = downladTimeTotal(gen);

    // simulate a download delay
    std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(randomDownloadTime)));

    // populate the data for each thread's download stats
    downloadStats.downloadStatus = true;
    downloadStats.fileName = fileName;
    downloadStats.downloadTime = randomDownloadTime;
    downloadStats.URL = URL;

    sem_post(semaphore);
}




int main(){

    // initialize seamphore to allow use our concurrent downloads global var
    sem_t semaphore;
    sem_init(&semaphore, 0, concurrent_downloads);

    // list of all available downloadable URL's
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
    "www.minecraft.com/download",
    "www.brave.com/download",
    "www.chrome.com/download",
    "www.firefox.com/download"
     };

    // list of all downloadable files, given a URL
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
    "minecraft",
    "brave",
    "chrome",
    "firefox"

    };


    // global array storing all downloads and their stats
    std::vector<Download_Stats> allDownloads(num_threads);

    // array to store each download in a thread
    std::vector<std::thread> threads;

    // adding each download into the array
    for (int i = 0; i < num_threads; ++i){

        threads.push_back(std::thread(ThreadHandler, &semaphore, URL[i], fileName[i], std::ref(allDownloads[i])));

    }

    // once the threads have completed, join them back together
    for (auto& thread: threads){
        thread.join();
    }

    // print each download and their respective stats
    for (Download_Stats& stats: allDownloads){

        std::cout 
        << "File:          " << stats.fileName 
        << "\nURL:           " << stats.URL
        << "\nDownload Time: " << std::fixed << std::setprecision(2) << stats.downloadTime << " Seconds"
        << "\nStatus:        " << (stats.downloadStatus ? "Success\n" : "Failure\n") << std::endl;
        
    }

    // remove the semaphore before exiting the program
    sem_destroy(&semaphore);

    return 0;
}