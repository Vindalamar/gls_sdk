add_library(auth auth.cpp)

target_link_libraries(auth PUBLIC cpr::cpr PUBLIC nlohmann_json::nlohmann_json)
