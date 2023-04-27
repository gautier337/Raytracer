/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** MathFactory
*/

#include "MathFactory.hpp"

RayTracer::Math::MathFactory::~MathFactory()
{
}

std::unique_ptr<RayTracer::Math::Vector3D> RayTracer::Math::MathFactory::createVector3D(
    double x,
    double y,
    double z
)
{
    return std::make_unique<RayTracer::Math::Vector3D>(x, y, z);
}

std::unique_ptr<RayTracer::Math::Point3D> RayTracer::Math::MathFactory::createPoint3D(
    double x,
    double y,
    double z
)
{
    return std::make_unique<RayTracer::Math::Point3D>(x, y, z);
}

extern "C" std::unique_ptr<RayTracer::Math::MathFactory> createMathFactory()
{
    return std::make_unique<RayTracer::Math::MathFactory>();
}
