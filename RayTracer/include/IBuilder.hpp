/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** IBuilder
*/

#pragma once
#include "CustomObject.hpp"

namespace RayTracer {
    class IBuilder {
        public:
            virtual ~IBuilder() = default;
            virtual CustomObject getObject() const = 0;
    };
}
