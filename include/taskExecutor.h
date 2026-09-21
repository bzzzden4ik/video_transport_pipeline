#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>
#include <queue>
#include <string>
#include "./types.h"
#include "./serverListener.h"


/**
 * Fake execution that simulates real model working. It helps to define concurrency working.
 * @param path_name  string value that let our function know current task.
 * @param result_var  bool that shows task result
*/
void executeProgram(const std::string& path_name, bool& result_var);


/**
 * Task function that starts in new thread.
 * @param isRunning  Bool that controlls working flow
 * @param tasks_queue  std::queue that organize queue of tasks. Pushing new files and poping old ones
 * @param queue_mutex  Mutex for files queue
 */
void taskObservation(bool& isRunning, const Config& config, std::queue<std::string>& tasks_queue, std::mutex& queue_mutex);