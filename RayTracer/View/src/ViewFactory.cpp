/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** ViewFactory
*/

#include "ViewFactory.hpp"

RayTracer::View::ViewFactory::~ViewFactory()
{
}

std::unique_ptr<RayTracer::View::Camera> RayTracer::View::ViewFactory::createCamera(
    RayTracer::Math::Point3D origin,
    RayTracer::Primitives::Rectangle3D screen
)
{
    return std::make_unique<RayTracer::View::Camera>(
        origin,
        screen
    );
}

std::unique_ptr<RayTracer::View::Ray> RayTracer::View::ViewFactory::createRay(
    RayTracer::Math::Point3D origin,
    RayTracer::Math::Vector3D direction
)
{
    return std::make_unique<RayTracer::View::Ray>(
        origin,
        direction
    );
}

extern "C" std::unique_ptr<RayTracer::View::ViewFactory> createViewFactory()
{
    return std::make_unique<RayTracer::View::ViewFactory>();
}
