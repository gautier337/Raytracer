/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Factory
*/

#include "Factory.hpp"
#include "DLLoader.hpp"

RayTracer::Factory::Factory()
{
}

RayTracer::Factory::~Factory()
{
}

void RayTracer::Factory::loadAllPlugins()
{
    // Lights
    this->loadPlugin("DirectionalLight", "./lights/DirectionalLight.so");

    // Math
    this->loadPlugin("Vector3D", "./math/Vector3D.so");
    this->loadPlugin("Point3D", "./math/Point3D.so");

    // Primitives
    this->loadPlugin("Rectangle3D", "./primitives/Rectangle3D.so");
    this->loadPlugin("Sphere", "./primitives/Sphere.so");

    // Render
    this->loadPlugin("Color", "./render/Color.so");

    // View
    this->loadPlugin("Camera", "./view/Camera.so");
    this->loadPlugin("Ray", "./view/Ray.so");
}

void RayTracer::Factory::loadPlugin(
    std::string const &name,
    std::string const &path
)
{
}

void RayTracer::Factory::unloadPlugin(std::string const &name)
{
}

void RayTracer::Factory::unloadAllPlugins()
{
    // .. complete the code
}

template<typename T, typename... Args>
std::unique_ptr<T> RayTracer::Factory::createPlugin(
    std::string const &name,
    Args... args
)
{
    auto it = this->plugins.find(name);
    if (it == this->plugins.end())
        throw std::runtime_error("Plugin not found");
    auto factory = it->second;
    auto ptr = factory();
    auto casted = dynamic_cast<T*>(ptr.get());
    if (casted == nullptr)
        throw std::runtime_error("Plugin does not implement requested interface");
    return std::unique_ptr<T>(casted);
}
