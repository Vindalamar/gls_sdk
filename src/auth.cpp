#include "auth.hpp"


std::string getToken(std::string username, std::string password) {
    json j = {
        {"username", username},
        {"password", password},
    };
    cpr::Response r = cpr::Post(cpr::Url{"https://back.glsystem.net/api/v1/auth/login/"},
                               cpr::Body{j.dump(2)}, cpr::Header{{"Content-Type", "application/json"}});
    if (r.status_code != 200)
        throw std::runtime_error("Auth Erorr code: " +  std::to_string(r.status_code));
    j = json::parse(r.text);
    return j["access_token"];
        
}