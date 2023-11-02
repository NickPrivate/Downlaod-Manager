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


void DownloadFile(const std::string& URL, const std::string& fileName, Download_Stats& downloadStats) {
    CURL* curl = curl_easy_init();
    if (curl) {
        // Initialize libcurl with the URL to download
        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

        // Open a file for writing the downloaded data
        std::ofstream file(fileName, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for writing: " << fileName << std::endl;
            downloadStats.downloadStatus = false;
            return;
        }

        // Set the write callback to save downloaded data to the file
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, PreDownload);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);

        // Perform the download
        auto start = std::chrono::system_clock::now();
        CURLcode res = curl_easy_perform(curl);
        auto end = std::chrono::system_clock::now();

        if (res != CURLE_OK) {
            std::cerr << "Download failed: " << curl_easy_strerror(res) << std::endl;
            downloadStats.downloadStatus = false;
        } else {
            downloadStats.downloadStatus = true;
            downloadStats.fileName = fileName;
            std::chrono::duration<double> elapsed_seconds = end - start;
            downloadStats.downloadTime = elapsed_seconds.count();
        }

        // Clean up
        curl_easy_cleanup(curl);
        file.close();
    }
}

void ThreadHandler(sem_t* semaphore, const std::string& URL, const std::string& fileName, Download_Stats& downloadStats) {
    sem_wait(semaphore);
    DownloadFile(URL, fileName, downloadStats);
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