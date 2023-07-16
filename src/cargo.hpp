#pragma once

#include "auth.hpp"

class Cargo {
    std::string title;
    int length;
    int width;
    int height;
    int mass;
    bool stacking;
    int stacking_limit;
    bool turnover;
    std::string article;
    int margin_length;
    int margin_width;
    int count;
    std::string color;

    public:

    Cargo(std::string title, int length, int width, int height, int mass, 
    bool stacking = true, int stacking_limit = 0, bool turnover = true, std::string article = "string", 
    int margin_length = 0, int margin_width = 0, int count = 1, std::string color = "string");

    json to_json();
};

class CargoGroup {
    std::string title;
    int pallet;
    std::vector<json> cargoes;

    public:

    CargoGroup(std::string title, int pallet);

    void addCargo(Cargo crgo);

    json to_json();
};