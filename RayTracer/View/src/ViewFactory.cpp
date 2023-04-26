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

std::unique_ptr<RayTracer::View::Camera> createCamera(
    RayTracer::Math::Point3D position,
    int width,
    int height,
    RayTracer::Math::Vector3D rotation,
    double fov
);

std::unique_ptr<RayTracer::View::Ray> createRay(
    RayTracer::Math::Point3D origin,
    RayTracer::Math::Vector3D direction
);

extern "C" std::unique_ptr<RayTracer::View::ViewFactory> createViewFactory()
{
    return std::make_unique<RayTracer::View::ViewFactory>();
}
