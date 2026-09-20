#include "../include/fileFinder.h"


void fileFinderInit (const Config& config, std::unordered_map<std::string, bool>& files, std::queue<std::string>& tasks_queue) {
    std::string full_path = config.path_name;
    size_t file_name_size = config.file_name.size();
    if (!std::filesystem::exists(full_path) || !std::filesystem::is_directory(full_path)) {
        throw std::invalid_argument("[Config] Wrong path name. There is no: " + full_path + " found.");
    }
    for (const auto& entry : std::filesystem::directory_iterator(full_path)) {
        auto name = entry.path().filename();
        if (entry.is_regular_file() && name.extension().string() == ".mp4" && name.string().substr(0, file_name_size + 1) == config.file_name + config.file_counter) {
            files[name.string()] = true;
            tasks_queue.push(name.string());
            std::cout << "[Observation] " << name << " initiated and added to queue.\n";
        }
    }
}

void lookForNewFiles (const Config& config, std::unordered_map<std::string, bool>& files, std::queue<std::string>& tasks_queue, std::mutex& files_mutex, std::mutex& queue_mutex) {
    std::string full_path = config.path_name;
    size_t file_name_size = config.file_name.size();
    for (const auto& entry : std::filesystem::directory_iterator(full_path)) {
        auto name = entry.path().filename();
        files_mutex.lock();
        if (files.contains(name.string())) {
            files_mutex.unlock();
            continue;
        }
        if (entry.is_regular_file() && name.extension().string() == ".mp4" && name.string().substr(0, file_name_size + 1) == config.file_name + config.file_counter && entry.file_size() >= config.file_size) {
            files[name.string()] = true;
            queue_mutex.lock();
            tasks_queue.push(name.string());
            std::cout << "[Observation] " << name << " just appeared and added to queue with size: " << entry.file_size() << ".\n";
            queue_mutex.unlock();
        }
        files_mutex.unlock();
    }
}