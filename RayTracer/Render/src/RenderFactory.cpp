/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** RenderFactory
*/

#include "RenderFactory.hpp"

RayTracer::Render::RenderFactory::~RenderFactory()
{
}

std::unique_ptr<RayTracer::View::Camera> createView(
    RayTracer::Math::Point3D origin,
    RayTracer::Primitives::Rectangle3D screen,
    std::string direction
)
{
    return std::make_unique<RayTracer::View::Camera>(
        origin,
        screen,
        direction
    );
}

extern "C" std::unique_ptr<RayTracer::Render::RenderFactory> createRenderFactory()
{
    return std::make_unique<RayTracer::Render::RenderFactory>();
}
