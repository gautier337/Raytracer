/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Factory
*/

#include "Factory.hpp"
#include <stdexcept>

RayTracer::Factory::Factory()
{
    this->loadAllPlugins();
}

RayTracer::Factory::~Factory()
{
    unloadAllPlugins();
}

void RayTracer::Factory::loadAllPlugins()
{
    // Lights
    this->loadPlugin("DirectionalLight", "./lights/DirectionalLight.so");

    // Math
    this->loadPlugin("Point3D", "./math/Point3D.so");
    this->loadPlugin("Vector3D", "./math/Vector3D.so");

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
    void *pluginHandle = dlopen(path.c_str(), RTLD_NOW);
    if (!pluginHandle)
        throw std::runtime_error("Failed to load plugin: " + name + " at path: " + path);

    void *constructorPtr = dlsym(pluginHandle, ("create" + name).c_str());
    if (!constructorPtr) {
        dlclose(pluginHandle);
        throw std::runtime_error("Failed to find constructor for plugin: " + name);
    }

    pluginHandles[name] = pluginHandle;
    pluginConstructors[name] = constructorPtr;
}

void RayTracer::Factory::unloadPlugin(std::string const &name)
{
    auto it = pluginHandles.find(name);
    if (it != pluginHandles.end()) {
        dlclose(it->second);
        pluginHandles.erase(it);
        pluginConstructors.erase(name);
    }
}

void RayTracer::Factory::unloadAllPlugins()
{
    for (auto &pair : pluginHandles)
        dlclose(pair.second);

    pluginHandles.clear();
    pluginConstructors.clear();
}

template<typename T, typename... Args>
std::unique_ptr<T> RayTracer::Factory::createPlugin(
    std::string const &name,
    Args... args
)
{
    auto it = pluginConstructors.find(name);
    if (it == pluginConstructors.end())
        throw std::runtime_error("Plugin not found: " + name);

    using ConstructorFunction = T*(*)(Args...);
    ConstructorFunction constructorFunc = reinterpret_cast<ConstructorFunction>(it->second);
    return std::unique_ptr<T>(constructorFunc(args...));
    return nullptr;
}
