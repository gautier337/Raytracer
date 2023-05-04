/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Factory
*/

#pragma once
#include "Library.hpp"
#include <string>
#include <memory>
#include <map>
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
            template <typename Signature, typename... Args>
            auto createPlugin(std::string const& name, Args&&... args)
            {
                auto it = libraries.find(name);
                if (it == libraries.end())
                    throw std::runtime_error("Failed to create plugin: " + name + " library not loaded");

                auto& lib = it->second;
                return lib.call<Signature, Args...>("create" + name, std::forward<Args>(args)...);
            }

        private:
            std::map<std::string, Library> libraries;
    };
}
