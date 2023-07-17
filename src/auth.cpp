#include "auth.hpp"


AuthBase getToken(std::string username, std::string password) {
    json j = {
        {"username", username},
        {"password", password},
    };
    cpr::Response r = cpr::Post(cpr::Url{"https://back.glsystem.net/api/v1/auth/login/"},
                               cpr::Body{j.dump(2)}, cpr::Header{{"Content-Type", "application/json"}});
    if (r.status_code != 200)
        throw std::runtime_error("Auth Erorr code: " +  std::to_string(r.status_code));
    j = json::parse(r.text);
    AuthBase a_base;
    a_base.access_token = j["access_token"];
    a_base.refresh_token = j["refresh_token"];
    return a_base;
}

void refreshToken(AuthBase* base) {
    json j = {
        {"refresh_token", base->refresh_token},
    };
    cpr::Response r = cpr::Post(cpr::Url{"https://back.glsystem.net/api/v1/auth/refresh/"},
                               cpr::Body{j.dump(2)}, cpr::Header{{"Content-Type", "application/json"}});
    if (r.status_code != 200)
        throw std::runtime_error("Refresh token Erorr code: " +  std::to_string(r.status_code));
    j = json::parse(r.text);
    base->access_token = j["access_token"];
}

void logout(std::string authToken) {
    cpr::Response r = cpr::Post(cpr::Url{"https://back.glsystem.net/api/v1/auth/logout/"},
                               cpr::Header{{"accept", "*/*"}}, cpr::Bearer{authToken});
    if (r.status_code != 200)
        throw std::runtime_error("Logout Erorr code: " +  std::to_string(r.status_code));
}