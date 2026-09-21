#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <string>
#include "../include/configReader.h"
#include "../include/fileFinder.h"
#include "../include/taskExecutor.h"
#include "../include/timer.h"
#include "../include/types.h"



int main () {
    Config config;
    std::unordered_map<std::string, bool> files;
    std::mutex files_mutex;
    std::queue<std::string> tasks_queue;
    std::mutex queue_mutex;
    bool isRunning = true;
    try {
        readConfig(config);
        fileFinderInit(config, files, tasks_queue);
        std::thread timer_thread(timerObservation, std::ref(isRunning), std::ref(config), std::ref(files), std::ref(tasks_queue), std::ref(files_mutex), std::ref(queue_mutex));
        std::thread finder_thread(taskObservation, std::ref(isRunning), std::ref(config), std::ref(tasks_queue), std::ref(queue_mutex));
        std::cout << "[System] Press any button to finish proccess...\n";
        std::cin.get();
        isRunning = false;
        timer_thread.join();
        finder_thread.join();
        std::cout << "[System] Program finished.\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}