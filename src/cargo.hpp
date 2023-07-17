#pragma once

#include "auth.hpp"

class Cargo {
    std::string title, article, color;
    int length, width, height, mass, id, stacking_limit, margin_length, margin_width, count;
    bool stacking, turnover;

    public:

    Cargo(std::string title, int length, int width, int height, int mass, int id = -1,
    bool stacking = true, int stacking_limit = 0, bool turnover = true, std::string article = "string", 
    int margin_length = 0, int margin_width = 0, int count = 1, std::string color = "#808080");

    Cargo(json j);

    json to_json();
    
    int get_id();
    void set_count(int c);
    void save_cargo(std::string authToken);
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

Cargo get_cargo(std::string authToken, int id);

std::vector<Cargo> get_cargo_list(std::string authToken);
