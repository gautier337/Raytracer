/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Library
*/

#pragma once
#include <string>
#include <memory>
#include <dlfcn.h>

namespace RayTracer {
    class Library {
        public:
            Library(std::string const &path);
            ~Library();
            Library(Library const &other);
            Library(Library &&other);
            Library &operator=(Library const &other);
            Library &operator=(Library &&other);
            template <typename Signature, typename... Args>
            auto call(std::string const &name, Args&&... args)
            {
                using FunctionPointer = Signature *;
                auto fn = reinterpret_cast<FunctionPointer>(dlsym(this->handle, name.c_str()));
                if (fn == nullptr)
                    throw std::runtime_error("Failed to load function: " + name + " does not exist");

                return fn(std::forward<Args>(args)...);
            }

        private:
            void *handle;
    };
}
