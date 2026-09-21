#pragma once
#include <iostream>
#include <string>
#include "./httplib.h"


/**
 * Simple server-side function
 * @param file_name
 */
std::string getServerRes(const std::string& file_name);