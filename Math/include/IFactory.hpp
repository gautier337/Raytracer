/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** IFactory
*/

#pragma once
#include <string>
#include <memory>
#include "IVector3D.hpp"

namespace Math {
    class IFactory {
        public:
            virtual ~IFactory() = default;
            virtual std::unique_ptr<Math::IVector3D> createVector3D() = 0;
            virtual std::unique_ptr<Math::IVector3D> createVector3D(
                float x,
                float y,
                float z
            ) = 0;
    };
};
