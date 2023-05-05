/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** IceCreamBuilder
*/

#include "IceCreamBuilder.hpp"

RayTracer::Builders::IceCreamBuilder::IceCreamBuilder() :
    iceCream()
{
}

RayTracer::Builders::IceCreamBuilder::~IceCreamBuilder()
{
}

RayTracer::Builders::IceCreamBuilder::IceCreamBuilder(
    const RayTracer::Builders::IceCreamBuilder &iceCreamBuilder
)
{
    this->iceCream = iceCreamBuilder.iceCream;
}

RayTracer::Builders::IceCreamBuilder::IceCreamBuilder(
    RayTracer::Builders::IceCreamBuilder &&iceCreamBuilder
)
{
    this->iceCream = std::move(iceCreamBuilder.iceCream);
}

RayTracer::Builders::IceCreamBuilder &RayTracer::Builders::IceCreamBuilder::operator=(
    const RayTracer::Builders::IceCreamBuilder &iceCreamBuilder
)
{
    this->iceCream = iceCreamBuilder.iceCream;
    return *this;
}

RayTracer::Builders::IceCreamBuilder &RayTracer::Builders::IceCreamBuilder::operator=(
    RayTracer::Builders::IceCreamBuilder &&iceCreamBuilder
)
{
    this->iceCream = std::move(iceCreamBuilder.iceCream);
    return *this;
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
    Primitives::Cone cone(
        center,
        axis,
        base_radius,
        apex_radius,
        height,
        color
    );
    this->iceCream.addPrimitive(cone);
}

void RayTracer::Builders::IceCreamBuilder::createScoop(
    Math::Point3D center,
    double radius,
    Render::Color color
)
{
    Primitives::Sphere sphere(
        center,
        radius,
        color
    );
    this->iceCream.addPrimitive(sphere);
}

RayTracer::CustomObject RayTracer::Builders::IceCreamBuilder::getObject() const
{
    return this->iceCream;
}
