/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Factory
*/

#include "Factory.hpp"
#include <stdexcept>
#include <iostream>

RayTracer::Factory::Factory()
{
    this->loadAllPlugins();
}

RayTracer::Factory::~Factory()
{
    this->unloadAllPlugins();
}

void RayTracer::Factory::loadAllPlugins()
{
    try {
        // Lights
        this->loadPlugin("AmbientLight", "./plugins/lights/AmbientLight.so");
        this->loadPlugin("DirectionalLight", "./plugins/lights/DirectionalLight.so");

        // Math
        this->loadPlugin("Point3D", "./plugins/math/Point3D.so");
        this->loadPlugin("Rectangle3D", "./plugins/math/Rectangle3D.so");
        this->loadPlugin("Vector3D", "./plugins/math/Vector3D.so");

        // Primitives
        this->loadPlugin("Cone", "./plugins/primitives/Cone.so");
        this->loadPlugin("Plane", "./plugins/primitives/Plane.so");
        this->loadPlugin("Sphere", "./plugins/primitives/Sphere.so");
        this->loadPlugin("Cone", "./plugins/primitives/Cone.so");
        this->loadPlugin("Cylinder", "./plugins/primitives/Cylinder.so");

        // Render
        this->loadPlugin("Color", "./plugins/render/Color.so");

        // View
        this->loadPlugin("Camera", "./plugins/view/Camera.so");
        this->loadPlugin("Ray", "./plugins/view/Ray.so");
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void RayTracer::Factory::loadPlugin(
    std::string const &name,
    std::string const &path
)
{
    if (this->libraries.find(name) != this->libraries.end())
        throw std::runtime_error("Library already loaded: " + name);
    Library lib(path);

    this->libraries.emplace(name, std::move(lib));
}

void RayTracer::Factory::unloadPlugin(std::string const &name)
{
    this->libraries.erase(name);
}

void RayTracer::Factory::unloadAllPlugins()
{
    this->libraries.clear();
}
