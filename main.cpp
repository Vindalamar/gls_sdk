#include <iostream>

// #include <auth.hpp>

// #include <cargo.hpp>

#include <calculation.hpp>



#include <windows.h>     //for function sleep


int main(int argc, char** argv) {

    // Авторизация пользователя, возвращение структуры с токенами авторизации и обновления
    AuthBase base = getToken("user", "pass");
    std::string token = base.access_token;
    
    // Создание проекта, возвращение id проекта
    int pr_id = project_create(token, "TestProject");

    // Возвращение списка названий грузовых пространств по их типа (pallet, container, van, truck )
    // std::vector<std::string> r = get_GP_titlelist(token, space_type::container);

    // Получить id грузового пространства по названию
    int gp_id = get_GP_id(token, space_type::container, "40' DV (valid)");

    // std::vector<Cargo> res = get_cargo_list(token);

    // Создание груза и сохранение на сервер
    Cargo c = Cargo(std::string("new"), 95, 95 , 95, 100);
    c.save_cargo(token);

    // Получение груза с сервера
    Cargo h = get_cargo(token, c.getId());

    // Изменение названия груза
    c.setTitle("old");

    // Обновления токена через токен обновления
    refreshToken(&base);

    // Вывод токена авторизации из системы (Logout)
    logout(token);

    token = base.access_token;
    
    // Обновление груза на сервере
    refresh_cargo(token, c, c.getId());

    // logout(token);

    // Удаление груза с сервера
    // delete_cargo(token ,c.getId());
    
    // Создание группы грузов для вычисления
    Cargo z = Cargo(std::string("old"), 80, 80 , 80, 100);
    CargoGroup cg =  CargoGroup(std::string("ch"), 0);
    
    // Добавление группу грузов
    cg.addCargo(&c);
    cg.addCargo(&z);

    // Создание вычисления с использованием токена, id проекта, массив id грузовых пространств, массив групп грузов. 
    // Возвращает id вычисления
    int cal_id = create_calculation(token, pr_id,  {gp_id} , {cg});

    // Дает время серверу на вычисление
    Sleep(5000);

    // Получение результата вычисления, в качестве json файла
    json j = get_calc_results(token, pr_id, cal_id);

    std::cout << j.dump(2);

    std::cout << cg.to_json().dump(2);

    // Выведение токена
    logout(token);
    
    return 0;
}