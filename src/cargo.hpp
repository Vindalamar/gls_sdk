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
    
    int getId();

    std::string getTitle();
    void setTitle(std::string t);

    std::string getArticle();
    void setArticle(std::string a);

    std::string getColor();
    void setColor(std::string c);

    int getLength();
    void setLength(int l);

    int getWidth();
    void setWidth(int w);

    int getHeight();
    void setHeight(int h);

    int getMass();
    void setMass(int m);
    
    int getStackLimit();
    void setStackLimit(int sl);

    int getMarginLen();
    void setMarginLen(int ml);

    int getMarginWidth();
    void setMarginWidth(int mw);

    int getCount();
    void setCount(int c);

    bool getStacking();
    void setStacking(bool s);

    bool getTurnover();
    void setTurnover(bool t);

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

void delete_cargo(std::string authToken, int id);

void refresh_cargo(std::string authToken, Cargo cargo, int id);

std::vector<Cargo> get_cargo_list(std::string authToken);
