#include <iostream>

// #include <auth.hpp>

// #include <cargo.hpp>

#include <calculation.hpp>



#include <windows.h>     //for using the function sleep


int main(int argc, char** argv) {

    AuthBase base = getToken("user", "pass");
    std::string token = base.access_token;
    
    // int pr_id = project_create(token, "TestProject");
    std::vector<std::string> r = get_GP_titlelist(token, space_type::container);
    // int gp_id = get_GP_id(token, space_type::container, "40' DV (valid)");

    std::vector<Cargo> res = get_cargo_list(token);

    Cargo c = Cargo(std::string("new"), 95, 95 , 95, 100);
    c.save_cargo(token);

    Cargo h = get_cargo(token, c.getId());

    c.setTitle("old");

    refreshToken(&base);

    logout(token);

    token = base.access_token;
    
    refresh_cargo(token, c, c.getId());

    // logout(token);

    delete_cargo(token ,c.getId());
    
    // Cargo z = Cargo(std::string("old"), 80, 80 , 80, 100);
    // CargoGroup cg =  CargoGroup(std::string("ch"), 0);
    
    // cg.addCargo(c);
    // cg.addCargo(z);

    // int cal_id = create_calculation(token, pr_id,  {gp_id} , {cg});

    // Sleep(5000);

    // json j = get_calc_results(token, pr_id, cal_id);

    // std::cout << j.dump(2);

    return 0;
}