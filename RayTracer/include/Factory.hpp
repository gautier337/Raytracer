/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Factory
*/

#pragma once
#include <string>
#include <memory>
#include <map>
#include <functional>
#include <dlfcn.h>

namespace RayTracer {
    class Factory {
        public:
            Factory();
            ~Factory();
            void loadAllPlugins();
            void loadPlugin(
                std::string const &name,
                std::string const &path
            );
            void unloadPlugin(std::string const &name);
            void unloadAllPlugins();
            template<typename T, typename... Args>
            std::unique_ptr<T> createPlugin(
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

        private:
            std::map<std::string, void*> pluginHandles;
            std::map<std::string, void*> pluginConstructors;
    };
}
