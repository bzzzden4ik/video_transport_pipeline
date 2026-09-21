#pragma once
#include <iostream>
#include <string>
#include "./httplib.h"


/**
 * Simple server-side function that request and return answer from server where model works
 * @param file_name  path_name to current file
 */
std::string getServerRes(const std::string& file_name);