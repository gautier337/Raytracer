/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** PrimitivesFactory
*/

#pragma once
#include "IFactory.hpp"
#include "Sphere.hpp"
#include "Rectangle3D.hpp"
#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "Color.hpp"
#include <memory>

namespace RayTracer {
    namespace Primitives {
        class PrimitivesFactory : public IFactory {
            public:
                PrimitivesFactory() = default;
                ~PrimitivesFactory() override;
                std::unique_ptr<RayTracer::Primitives::Sphere> createSphere(
                    RayTracer::Math::Point3D origin,
                    double radius,
                    RayTracer::Render::Color color
                );
                std::unique_ptr<RayTracer::Primitives::Rectangle3D> createRectangle3D(
                    RayTracer::Math::Point3D origin,
                    RayTracer::Math::Vector3D bottom_side,
                    RayTracer::Math::Vector3D left_side,
                    RayTracer::Render::Color color
                );
        };
    }
}
