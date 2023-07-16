#include "cargo.hpp"

Cargo::Cargo(std::string title, int length, int width, int height, int mass,
    bool stacking, int stacking_limit, bool turnover, std::string article, 
    int margin_length, int margin_width, int count, std::string color): 
    title{title}, length{length}, width{width}, height{height}, mass{mass}, stacking{stacking}, stacking_limit{stacking_limit}, 
    turnover{turnover}, article{article}, margin_length{margin_length}, margin_width{margin_width}, count{count}, color{color} {}

json Cargo::to_json() {
    json j = {
        {"title", title},
        {"length", length},
        {"width", width},
        {"height", height},
        {"mass", mass},
        {"stacking", stacking},
        {"stacking_limit", stacking_limit},
        {"turnover", turnover},
        {"article", article},
        {"margin_length", margin_length},
        {"margin_width", margin_width},
        {"count", count},
        {"color", color},
    };
    return j;
}

CargoGroup:: CargoGroup(std::string title, int pallet): title{title}, pallet{pallet} {}

void CargoGroup::addCargo(Cargo crgo) {
    cargoes.push_back(crgo.to_json());
}

json CargoGroup::to_json() {
    json j = {
        {"title", title},
        {"pallet", pallet},
        {"cargoes", cargoes},
        {"sort", 1},
    };
    return j;
}
