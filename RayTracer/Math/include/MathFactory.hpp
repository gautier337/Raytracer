/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** MathFactory
*/

#pragma once
#include "IFactory.hpp"
#include "Vector3D.hpp"
#include "Point3D.hpp"
#include <memory>

namespace RayTracer {
    namespace Math {
        class MathFactory : public IFactory {
            public:
                MathFactory() = default;
                ~MathFactory() override;
                std::unique_ptr<RayTracer::Math::Vector3D> createVector3D(
                    double x,
                    double y,
                    double z
                );
                std::unique_ptr<RayTracer::Math::Point3D> createPoint3D(
                    double x,
                    double y,
                    double z
                );
        };
    }
}
