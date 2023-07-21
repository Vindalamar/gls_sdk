#pragma once

#include "cargo.hpp"

enum class space_type {pallet, container, van, truck};

std::string st_to_string(space_type n);


int project_create(std::string authToken, std::string title);

std::vector<std::string> get_GP_titlelist(std::string authToken, space_type cargo_space_type);

int get_GP_id(std::string authToken, space_type cargo_space_type, std::string title__icontains);

int create_calculation(std::string authToken, int projId, std::vector<int> gpIds, std::vector<CargoGroup> groups);

json get_calc_results(std::string authToken, int projId, int calcId);
