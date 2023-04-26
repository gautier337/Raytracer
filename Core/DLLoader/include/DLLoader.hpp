/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** DLLoader
*/

#pragma once
#include <string>
#include <dlfcn.h>
#include <memory>
#include <functional>
#include <iostream>

namespace Core {
    class DLLoader {
        public:
            DLLoader() = delete;
            DLLoader(std::string const &path);
            ~DLLoader();

            template<class T>
            T getInstance(const std::string &path) const
            {
                void *gptr = dlsym(this->_handle, path.c_str());

                if (gptr == nullptr) {
                    throw std::exception();
                    exit(84);
                }
                return std::move(reinterpret_cast<T>(gptr));
            }

            void changeLib(std::string const &path);

        protected:
            void *_handle;
    };
}
