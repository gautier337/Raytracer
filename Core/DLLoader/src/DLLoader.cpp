/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** DLLoader
*/

#include "DLLoader.hpp"
#include <exception>
#include <iostream>
#include <sstream>

Core::DLLoader::DLLoader(std::string const &path)
    : _handle(nullptr)
{
    FILE *file = fopen(path.c_str(), "r");
    if (file == nullptr)
        throw std::runtime_error("Failed to load library: " + path + " does not exist");
    fclose(file);

    this->_handle = dlopen(path.c_str(), RTLD_LAZY);
    if (this->_handle == nullptr)
        throw std::runtime_error("Failed to load library: " + std::string(dlerror()));
}

Core::DLLoader::~DLLoader()
{
    if (this->_handle != nullptr)
        dlclose(this->_handle);
}

void Core::DLLoader::changeLib(std::string const &path)
{
    if (this->_handle != nullptr)
        dlclose(this->_handle);

    FILE *file = fopen(path.c_str(), "r");
    if (file == nullptr)
        throw std::runtime_error("Failed to load library: " + path + " does not exist");
    fclose(file);

    this->_handle = dlopen(path.c_str(), RTLD_LAZY);
    if (this->_handle == nullptr)
        throw std::runtime_error("Failed to load library: " + std::string(dlerror()));
}
