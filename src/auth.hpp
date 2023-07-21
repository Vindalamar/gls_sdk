#pragma once

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

// for convenience
using json = nlohmann::json;

struct AuthBase {
    std::string access_token;
    std::string refresh_token;
};

AuthBase getToken(std::string username, std::string password);

void refreshToken(AuthBase* base);

void logout(std::string authToken);
