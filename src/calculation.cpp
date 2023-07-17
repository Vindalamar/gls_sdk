#include "calculation.hpp"


std::string st_to_string(space_type n) {
    switch (n) {
    case space_type::pallet: return "pallet";
    case space_type::container: return "container";
    case space_type::van: return "van";
    case space_type::truck: return "truck";
    default: return "";
    }
}

int project_create(std::string authToken, std::string title) {
    json j = {
        {"title", title},
    };
    cpr::Response r = cpr::Post(cpr::Url{"https://back.glsystem.net/api/v1/project/"},
                               cpr::Body{j.dump(2)}, cpr::Header{{"Content-Type", "application/json"}}, cpr::Bearer{authToken});
    if (r.status_code != 201)
        throw std::runtime_error("Project create Erorr code: " +  std::to_string(r.status_code));
    j = json::parse(r.text);
    return j["id"];
}

std::vector<std::string> get_GP_titlelist(std::string authToken, space_type cargo_space_type) {
    std::string st = st_to_string(cargo_space_type);
    cpr::Response r = cpr::Get(cpr::Url{"https://back.glsystem.net/api/v1/cargo-space/"},
                               cpr::Parameters{{"cargo_space_type", st}, {"page_size", std::to_string(INT_MAX)}}, 
                               cpr::Header{{"Content-Type", "application/json"}}, cpr::Bearer{authToken});
    std::vector<std::string> res;
    if (r.status_code != 200)
        throw std::runtime_error("Get title-list Erorr code: " +  std::to_string(r.status_code));
    json j = json::parse(r.text);

    for (size_t i = 0; i < j["count"]; i++)
        res.push_back(j["results"][i]["title"]);

    return res;
}

int get_GP_id(std::string authToken, space_type cargo_space_type, std::string title__icontains) {
    std::string st = st_to_string(cargo_space_type);
    cpr::Response r = cpr::Get(cpr::Url{"https://back.glsystem.net/api/v1/cargo-space/"},
                               cpr::Parameters{{"cargo_space_type", st}, {"title__icontains", title__icontains}}, 
                               cpr::Header{{"Content-Type", "application/json"}}, cpr::Bearer{authToken});
    if (r.status_code != 200)
       throw std::runtime_error("Get titlelist Erorr code: " +  std::to_string(r.status_code));
    json j = json::parse(r.text);
    return j["results"][0]["id"];
}

int create_calculation(std::string authToken, int projId, std::vector<int> gpIds, std::vector<CargoGroup> groups) {
    std::vector<json> jg;
    for (CargoGroup cg : groups)
        jg.push_back(cg.to_json());
    
    json j = {
        {"project", projId},
        {"input_data", {
            {"cargo_spaces", gpIds},
            {"groups", jg}
        }},
        {"status", "new"},
        {"external_api", true}
    };

    cpr::Response r = cpr::Post(cpr::Url{"https://back.glsystem.net/api/v1/calculation/"},
                               cpr::Header{{"Content-Type", "application/json"}}, 
                               cpr::Bearer{authToken}, cpr::Body(j.dump(2)));

    if (r.status_code != 201)
        throw std::runtime_error("Calculation create Erorr code: " +  std::to_string(r.status_code));
    
    j = json::parse(r.text);
    return j["id"];
}

json get_calc_results(std::string authToken, int projId, int calcId) {
    json j;
    cpr::Response r = cpr::Get(cpr::Url{"https://back.glsystem.net/api/v1/project/" +  std::to_string(projId) + "/"},
                               cpr::Parameters{{"calculation_id", std::to_string(calcId)}},
                               cpr::Header{{"Content-Type", "application/json"}}, cpr::Bearer{authToken});


    if (r.status_code != 200)
        throw std::runtime_error("Calculation result Erorr code: " +  std::to_string(r.status_code));
    
    j = json::parse(r.text);


    return j;
}
