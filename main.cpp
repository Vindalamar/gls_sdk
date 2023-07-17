#include <iostream>

// #include <auth.hpp>

// #include <cargo.hpp>

#include <calculation.hpp>



#include <windows.h>     //for using the function sleep


int main(int argc, char** argv) {

    std::string token = getToken("username", "pass");
    int pr_id = project_create(token, "TestProject");
    // std::vector<std::string> r = get_GP_titlelist(token, space_type::container);
    int gp_id = get_GP_id(token, space_type::container, "40' DV (valid)");

    Cargo c = Cargo(std::string("new"), 95, 95 , 95, 100);
    Cargo z = Cargo(std::string("old"), 80, 80 , 80, 100);
    CargoGroup cg =  CargoGroup(std::string("ch"), 0);
    
    cg.addCargo(c);
    cg.addCargo(z);

    int cal_id = create_calculation(token, pr_id,  {gp_id} , {cg});

    Sleep(5000);

    json j = get_calc_results(token, pr_id, cal_id);

    std::cout << j.dump(2);

    return 0;
}