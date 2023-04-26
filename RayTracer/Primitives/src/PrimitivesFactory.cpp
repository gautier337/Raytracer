/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** PrimitivesFactory
*/

#include "PrimitivesFactory.hpp"

RayTracer::Primitives::PrimitivesFactory::~PrimitivesFactory()
{
}

std::unique_ptr<RayTracer::Primitives::Sphere> createSphere(
    RayTracer::Math::Point3D origin,
    double radius,
    RayTracer::Render::Color color
)
{
    return std::make_unique<RayTracer::Primitives::Sphere>(
        origin,
        radius,
        color
    );
}

std::unique_ptr<RayTracer::Primitives::Rectangle3D> createRectangle3D(
    RayTracer::Math::Point3D origin,
    RayTracer::Math::Vector3D bottom_side,
    RayTracer::Math::Vector3D left_side,
    RayTracer::Render::Color color
)
{
    return std::make_unique<RayTracer::Primitives::Rectangle3D>(
        origin,
        bottom_side,
        left_side,
        color
    );
}

extern "C" std::unique_ptr<RayTracer::Primitives::PrimitivesFactory> createPrimitivesFactory()
{
    return std::make_unique<RayTracer::Primitives::PrimitivesFactory>();
}
