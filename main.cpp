#include <iostream>

#include <auth.hpp>


int main(int argc, char** argv) {

    std::cout << getToken("username", "password");

    return 0;
}