/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Factory
*/

#pragma once
#include "IFactory.hpp"
#include <functional>
#include <memory>
#include <vector>
#include <map>

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
            );

        private:
            std::map<std::string, std::function<std::unique_ptr<IFactory>(void)>> plugins;
    };
}
