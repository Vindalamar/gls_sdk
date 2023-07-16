#pragma once

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

// for convenience
using json = nlohmann::json;

std::string getToken(std::string username, std::string password);