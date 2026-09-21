#include "../include/taskExecutor.h"


void executeProgram(const std::string& path_name, bool& result_var) {
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution distr(0.5);
    bool result = distr(gen);
    result_var = result;
}

void taskObservation(bool& isRunning, const Config& config, std::queue<std::string>& tasks_queue, std::mutex& queue_mutex) {
    std::cout << "[System] Task Thread just started.\n";
    bool isTask = true;
    while (isRunning) {
        bool result;
        queue_mutex.lock();
        if (!tasks_queue.empty()) {
            isTask = true;
            std::string current_task = tasks_queue.front();
            tasks_queue.pop();
            queue_mutex.unlock();
            std::cout << "[Task] \"" << current_task << "\" | Starting\n";
            std::cout << getServerRes(config.path_name + current_task);
            // executeProgram(current_task, result);
            std::cout << "[Task] \"" << current_task << "\" | Finished\n";
        } else {
            queue_mutex.unlock();
            if (isTask) {
                std::cout << "[Task] Queue is empty.\n";
                isTask = false;
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "[System] Task Thread just finished.\n";
}