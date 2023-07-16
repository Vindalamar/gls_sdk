add_library(auth auth.cpp)
add_library(cargo cargo.cpp)
add_library(calc calculation.cpp)

target_link_libraries(cargo PUBLIC cpr::cpr PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(auth PUBLIC cpr::cpr PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(calc PUBLIC cpr::cpr PUBLIC nlohmann_json::nlohmann_json cargo)

