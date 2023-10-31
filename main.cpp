#include <iostream>
#include <thread>
#include <semaphore.h>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>


#define num_threads 10
#define concurrent_downloads 6

struct Download_Stats {
    std::string fileName;
    float downloadTime;
    bool downloadStatus;
};

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

}




int main(){






    return 0;
}