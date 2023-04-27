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

std::unique_ptr<RayTracer::Render::Color> RayTracer::Render::RenderFactory::createColor(
    double r,
    double g,
    double b,
    double a
)
{
    return std::make_unique<RayTracer::Render::Color>(r, g, b, a);
}

extern "C" std::unique_ptr<RayTracer::Render::RenderFactory> createRenderFactory()
{
    return std::make_unique<RayTracer::Render::RenderFactory>();
}
