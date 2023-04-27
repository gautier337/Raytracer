/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** LightsFactory
*/

#include "LightsFactory.hpp"

RayTracer::Lights::LightsFactory::~LightsFactory()
{
}

std::unique_ptr<RayTracer::Lights::DirectionalLight> createDirectionalLight(
    RayTracer::Math::Point3D origin,
    RayTracer::Math::Vector3D direction,
    double brightness,
    RayTracer::Render::Color color
)
{
    return std::make_unique<RayTracer::Lights::DirectionalLight>(
        origin,
        direction,
        brightness,
        color
    );
}

extern "C" std::unique_ptr<RayTracer::Lights::LightsFactory> LightsFactory()
{
    return std::make_unique<RayTracer::Lights::LightsFactory>();
}
