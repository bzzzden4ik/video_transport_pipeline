#include "../include/serverListener.h"


std::string getServerRes(const std::string& fileName) {
    if (fileName.empty()) {
        throw std::invalid_argument("Wrong path_name recieved");
    }
    httplib::Client cli("http://127.0.0.1:8080");
    std::string result = "";
    if (auto res = cli.Get("/ai?path=" + fileName)) {
        result = res->body;
    } else {
        throw res.error();
    }
    return result;
}