/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** IceCreamBuilder
*/

#include "IceCreamBuilder.hpp"

RayTracer::Builders::IceCreamBuilder::IceCreamBuilder()
{
}

RayTracer::Builders::IceCreamBuilder::~IceCreamBuilder()
{
}

RayTracer::Builders::IceCreamBuilder::IceCreamBuilder(
    const RayTracer::Builders::IceCreamBuilder &iceCreamBuilder
)
{
    this->cone = iceCreamBuilder.cone;
    this->scoops = iceCreamBuilder.scoops;
}

RayTracer::Builders::IceCreamBuilder::IceCreamBuilder(
    RayTracer::Builders::IceCreamBuilder &&iceCreamBuilder
)
{
    this->cone = std::move(iceCreamBuilder.cone);
    this->scoops = std::move(iceCreamBuilder.scoops);
}

RayTracer::Builders::IceCreamBuilder &RayTracer::Builders::IceCreamBuilder::operator=(
    const RayTracer::Builders::IceCreamBuilder &iceCreamBuilder
)
{
    this->cone = iceCreamBuilder.cone;
    this->scoops = iceCreamBuilder.scoops;
    return *this;
}

RayTracer::Builders::IceCreamBuilder &RayTracer::Builders::IceCreamBuilder::operator=(
    RayTracer::Builders::IceCreamBuilder &&iceCreamBuilder
)
{
    this->cone = std::move(iceCreamBuilder.cone);
    this->scoops = std::move(iceCreamBuilder.scoops);
    return (*this);
}

void RayTracer::Builders::IceCreamBuilder::createCone(
    Math::Point3D center,
    Math::Vector3D axis,
    double base_radius,
    double apex_radius,
    double height,
    Render::Color color
)
{
    this->cone = Primitives::Cone(center, axis, base_radius, apex_radius, height, color);
}

void RayTracer::Builders::IceCreamBuilder::createScoop(
    Math::Point3D center,
    double radius,
    Render::Color color
)
{
    this->scoops.push_back(Primitives::Sphere(center, radius, color));
}
