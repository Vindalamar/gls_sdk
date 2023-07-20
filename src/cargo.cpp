#include "cargo.hpp"

Cargo::Cargo(std::string title, int length, int width, int height, int mass, int id,
    bool stacking, int stacking_limit, bool turnover, std::string article, 
    int margin_length, int margin_width, int count, std::string color): 
    title{title}, length{length}, width{width}, height{height}, mass{mass}, stacking{stacking}, stacking_limit{stacking_limit}, 
    turnover{turnover}, article{article}, margin_length{margin_length}, margin_width{margin_width}, count{count}, color{color} {}

Cargo::Cargo(json j): title{j["title"]}, length{j["length"]}, width{j["width"]}, height{j["height"]}, mass{j["mass"]}, 
                id{j["id"]}, stacking{j["stacking"]}, stacking_limit{j["stacking_limit"]}, turnover{j["turnover"]}, article{j["article"]}, 
                margin_length{j["margin_length"]},  margin_width{j["margin_width"]}, count{1}, color{j["color"]} {}

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

void Cargo::save_cargo(std::string authToken) {
    json j = this->to_json();
    cpr::Response r = cpr::Post(cpr::Url{"https://back.glsystem.net/api/v1/cargo/"},
                            cpr::Header{{"Content-Type", "application/json"}}, cpr::Body(j.dump(2)), cpr::Bearer{authToken});
    if (r.status_code != 201)
        throw std::runtime_error("save-cargo Erorr code: " +  std::to_string(r.status_code));
    j = json::parse(r.text);
    id = j["id"];
}

CargoGroup:: CargoGroup(std::string title, int pallet): title{title}, pallet{pallet} {}

void CargoGroup::addCargo(Cargo* crgo) {
    cargoes.push_back(crgo->to_json());
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

Cargo get_cargo(std::string authToken, int id) {
    cpr::Response r = cpr::Get(cpr::Url{"https://back.glsystem.net/api/v1/cargo/" + std::to_string(id) + '/'},
                        cpr::Header{{"Content-Type", "application/json"}}, cpr::Bearer{authToken});
    if (r.status_code != 200)
        throw std::runtime_error("Get cargo Erorr code: " +  std::to_string(r.status_code));
    json j = json::parse(r.text);
    return Cargo(j);
}

void delete_cargo(std::string authToken, int id) {
    cpr::Response r = cpr::Delete(cpr::Url{"https://back.glsystem.net/api/v1/cargo/" + std::to_string(id) + '/'},
                        cpr::Header{{"Content-Type", "application/json"}}, cpr::Bearer{authToken});
    if (r.status_code != 204)
        throw std::runtime_error("Delete cargo Erorr code: " +  std::to_string(r.status_code));       
}

void refresh_cargo(std::string authToken, Cargo cargo, int id) {
    json j = cargo.to_json();
    cpr::Response r = cpr::Put(cpr::Url{"https://back.glsystem.net/api/v1/cargo/" + std::to_string(id) + '/'},
                            cpr::Header{{"Content-Type", "application/json"}}, cpr::Body(j.dump(2)), cpr::Bearer{authToken});
    if (r.status_code != 200)
        throw std::runtime_error("refresh-cargo Erorr code: " +  std::to_string(r.status_code));
}

std::vector<Cargo> get_cargo_list(std::string authToken) {
    cpr::Response r = cpr::Get(cpr::Url{"https://back.glsystem.net/api/v1/cargo/"},
                               cpr::Header{{"Content-Type", "application/json"}}, 
                               cpr::Parameters{{"page_size", std::to_string(INT_MAX)}}, cpr::Bearer{authToken});
    std::vector<Cargo> res;
    if (r.status_code != 200)
        throw std::runtime_error("Get cargo-list Erorr code: " +  std::to_string(r.status_code));
    json j = json::parse(r.text);

    for (size_t i = 0; i < j["count"]; i++)
        res.push_back(Cargo(j["results"][i]));

    return res;
}

int Cargo::getId() {
    return id;
}

std::string Cargo::getTitle() {
    return title;
}
void Cargo::setTitle(std::string t){
    title = t;
}

std::string Cargo::getArticle() {
    return article;
}
void Cargo::setArticle(std::string a){
    article = a;
}

std::string Cargo::getColor() {
    return color;
}
void Cargo::setColor(std::string c) {
    color = c;
}

int Cargo::getLength() {
    return length;
}
void Cargo::setLength(int l) {
    length = l;
}

int Cargo::getWidth() {
    return width;
}
void Cargo::setWidth(int w) {
    width = w;
}

int Cargo::getHeight() {
    return height;
}
void Cargo::setHeight(int h) {
    height = h;
}

int Cargo::getMass() {
    return mass;
}
void Cargo::setMass(int m) {
    mass = m;
}

int Cargo::getStackLimit() {
    return stacking_limit;
}
void Cargo::setStackLimit(int sl) {
    stacking_limit = sl;
}

int Cargo::getMarginLen() {
    return margin_length;
}
void Cargo::setMarginLen(int ml) {
    margin_length = ml;
}

 int Cargo::getMarginWidth(){
     return margin_width;
 }
 void Cargo::setMarginWidth(int mw) {
     margin_width = mw;
 }

 int Cargo::getCount() {
     return count;
 }
 void Cargo::setCount(int c) {
     count = c;
 }

 bool Cargo::getStacking() {
     return stacking;
 }
 void Cargo::setStacking(bool s) {
     stacking = s;
 }

 bool Cargo::getTurnover() {
     return turnover;
 }
 void Cargo::setTurnover(bool t) {
     turnover = t;
 }

