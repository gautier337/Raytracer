/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** IceCreamDirector
*/

#include "IceCreamDirector.hpp"
#include "Vector3D.hpp"
#include "Color.hpp"

RayTracer::Directors::IceCreamDirector::IceCreamDirector(
    Builders::IceCreamBuilder builder
)
{
    this->builder = builder;
}

RayTracer::Directors::IceCreamDirector::~IceCreamDirector()
{
}

RayTracer::Directors::IceCreamDirector::IceCreamDirector(
    const RayTracer::Directors::IceCreamDirector &iceCreamDirector
)
{
    this->builder = iceCreamDirector.builder;
}

RayTracer::Directors::IceCreamDirector::IceCreamDirector(
    RayTracer::Directors::IceCreamDirector &&iceCreamDirector
)
{
    this->builder = std::move(iceCreamDirector.builder);
}

RayTracer::Directors::IceCreamDirector &RayTracer::Directors::IceCreamDirector::operator=(
    const RayTracer::Directors::IceCreamDirector &iceCreamDirector
)
{
    this->builder = iceCreamDirector.builder;
    return *this;
}

RayTracer::Directors::IceCreamDirector &RayTracer::Directors::IceCreamDirector::operator=(
    RayTracer::Directors::IceCreamDirector &&iceCreamDirector
)
{
    this->builder = std::move(iceCreamDirector.builder);
    return *this;
}

void RayTracer::Directors::IceCreamDirector::make(
    std::string const &type,
    Math::Point3D position,
    double scale
)
{
    if (type == "one")
        return createOneScoopIceCream(position, scale);
    if (type == "two")
        return createTwoScoopsIceCream(position, scale);
    if (type == "three")
        return createThreeScoopsIceCream(position, scale);
    throw std::invalid_argument("Invalid type");
}

RayTracer::CustomObject RayTracer::Directors::IceCreamDirector::getObject() const
{
    return this->builder.getObject();
}

void RayTracer::Directors::IceCreamDirector::createOneScoopIceCream(
    Math::Point3D position,
    double scale
)
{
    // Cone
    this->builder.createCone(
        position,
        RayTracer::Math::Vector3D(0, 1, 0),
        0.470 * scale,
        0,
        1 * scale,
        RayTracer::Render::Color(0.960, 0.960, 0.862, 1)
    );

    // Strawberry scoop
    this->builder.createScoop(
        position + RayTracer::Math::Vector3D(0, 1 * scale, 0),
        0.470 * scale,
        RayTracer::Render::Color(0.749, 0.188, 0.188, 1)
    );
}

void RayTracer::Directors::IceCreamDirector::createTwoScoopsIceCream(
    Math::Point3D position,
    double scale
)
{
    // Cone
    this->builder.createCone(
        position,
        RayTracer::Math::Vector3D(0, 1, 0),
        0.470 * scale,
        0,
        1 * scale,
        RayTracer::Render::Color(0.960, 0.960, 0.862, 1)
    );

    // Strawberry scoop
    this->builder.createScoop(
        position + RayTracer::Math::Vector3D(-0.25, 1.25 * scale, 0),
        0.470 * scale,
        RayTracer::Render::Color(0.749, 0.188, 0.188, 1)
    );

    // Vanilla scoop
    this->builder.createScoop(
        position + RayTracer::Math::Vector3D(0.25, 1.25 * scale, 0),
        0.470 * scale,
        RayTracer::Render::Color(0.882, 0.807, 0.603, 1)
    );
}

void RayTracer::Directors::IceCreamDirector::createThreeScoopsIceCream(
    Math::Point3D position,
    double scale
)
{
    this->builder.createCone(
        position,
        RayTracer::Math::Vector3D(0, 1, 0),
        0.470 * scale,
        0,
        1 * scale,
        RayTracer::Render::Color(0.960, 0.960, 0.862, 1)
    );

    // Strawberry scoop
    this->builder.createScoop(
        position + RayTracer::Math::Vector3D(-0.25, 1.25 * scale, 0),
        0.470 * scale,
        RayTracer::Render::Color(0.749, 0.188, 0.188, 1)
    );

    // Vanilla scoop
    this->builder.createScoop(
        position + RayTracer::Math::Vector3D(0.25, 1.25 * scale, 0),
        0.470 * scale,
        RayTracer::Render::Color(0.882, 0.807, 0.603, 1)
    );

    // Chocolate scoop
    this->builder.createScoop(
        position + RayTracer::Math::Vector3D(0, 1.5 * scale, 0),
        0.470 * scale,
        RayTracer::Render::Color(0.384, 0.203, 0.070, 1)
    );
}

extern "C" std::unique_ptr<RayTracer::Directors::IceCreamDirector> createIceCreamDirector(
    RayTracer::Builders::IceCreamBuilder builder
)
{
    return std::make_unique<RayTracer::Directors::IceCreamDirector>(builder);
}
