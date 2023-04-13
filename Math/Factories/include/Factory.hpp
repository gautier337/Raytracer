/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Factory
*/

#pragma once
#include "IFactory.hpp"

namespace Math {
    class Factory : public IFactory {
        public:
            Factory() = default;
            ~Factory() override;
            std::unique_ptr<Math::IVector3D> createVector3D() override;
            std::unique_ptr<Math::IVector3D> createVector3D(
                float x,
                float y,
                float z
            ) override;
    };
}
