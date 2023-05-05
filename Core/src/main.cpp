/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** main
*/

#include "RayTracer.hpp"
#include <string>

int check_env()
{
    const char *display = std::getenv("DISPLAY");

    if (display != nullptr)
        return SUCCESS;
    std::cerr << "Error: DISPLAY is not set" << std::endl;
    return ERROR;
}

int main(int argc, char **argv)
{
    if (argc != 2 || std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
        std::cerr << "USAGE: ./raytracer <SCENE_FILE>" << std::endl << "  SCENE_FILE: scene configuration" << std::endl;
        return ERROR;
    }
    if (check_env() == ERROR)
        return ERROR;
    return raytracer(argv[1]);
}
