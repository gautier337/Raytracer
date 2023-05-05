/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** IDirector
*/

#pragma once
#include "IBuilder.hpp"
#include <string>

namespace RayTracer {
    class IDirector {
        public:
            virtual ~IDirector() = default;
            virtual void setBuilder(IBuilder builder) = 0;
            virtual void make(std::string const &type) = 0;
    };
}
