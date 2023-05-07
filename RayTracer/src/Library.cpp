/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Library
*/

#include "Library.hpp"
#include <stdexcept>

RayTracer::Library::Library(std::string const &path)
{
    FILE *file = fopen(path.c_str(), "r");
    if (file == nullptr)
        throw std::runtime_error("Failed to load plugin: " + path + " does not exist");
    fclose(file);

    this->handle = dlopen(path.c_str(), RTLD_LAZY);
    if (this->handle == nullptr)
        throw std::runtime_error("Failed to load library: " + std::string(dlerror()));
}

RayTracer::Library::~Library()
{
    if (this->handle != nullptr)
        dlclose(this->handle);
}

RayTracer::Library::Library(Library const &other)
{
    if (other.handle != nullptr)
        this->handle = other.handle;
}

RayTracer::Library::Library(Library &&other)
{
    if (other.handle != nullptr)
        this->handle = other.handle;
}

RayTracer::Library &RayTracer::Library::operator=(Library const &other)
{
    if (this != &other && other.handle != nullptr)
        this->handle = other.handle;

    return *this;
}

RayTracer::Library &RayTracer::Library::operator=(Library &&other)
{
    if (this != &other && other.handle != nullptr)
        this->handle = other.handle;

    return *this;
}
