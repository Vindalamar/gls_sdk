Simple C++ sdk for Garpix Load System

Simple use case in the [main.cpp](https://github.com/Vindalamar/gls_sdk/blob/main/main.cpp)

## build
```shell
mkdir build
cd build
cmake ..
```
## Authorization components
```shell
struct AuthBase {
    std::string access_token;
    std::string refresh_token;
};

AuthBase getToken("username", "password");
void refreshToken(&AuthBase);
void logout(token);
```

## Cargo components

```shell
Cargo(std::string title, int length, int width, int height, int mass, int id = -1,
    bool stacking = true, int stacking_limit = 0, bool turnover = true, std::string article = "string", 
    int margin_length = 0, int margin_width = 0, int count = 1, std::string color = "#808080");
Cargo(json j);
void Cargo::save_cargo(std::string authToken); // Save cargo on server

CargoGroup(std::string title, int pallet);
void CargoGroup::addCargo(Cargo* crgo);

Cargo get_cargo(std::string authToken, int id); // Get cargo from server
void delete_cargo(std::string authToken, int id); // Delete cargo from server
void refresh_cargo(std::string authToken, Cargo cargo, int id); // Refresh server cargo with passed as asrgument Cargo
```
## Calculation components

```shell
int project_create(std::string authToken, std::string title); // Returns project id
int get_GP_id(std::string authToken, space_type cargo_space_type, std::string title__icontains); // Retern Cargo Space id

// Arguments for creating calculation are Authorization token, project id, cargo space id, and cargo groups
int create_calculation(std::string authToken, int projId, std::vector<int> gpIds, std::vector<CargoGroup> groups); // Returns id of calculation
json get_calc_results(std::string authToken, int projId, int calcId); // returns result json
```
