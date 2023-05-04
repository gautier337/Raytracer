/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** DirectionalLight.cpp
*/

#include "DirectionalLight.hpp"
#include <memory>

RayTracer::Lights::DirectionalLight::DirectionalLight() :
    origin(),
    direction()
{
}

RayTracer::Lights::DirectionalLight::~DirectionalLight()
{
}


RayTracer::Lights::DirectionalLight::DirectionalLight(
    Math::Point3D origin,
    Math::Vector3D direction,
    double brightness,
    Render::Color color
) :
    origin(origin),
    direction(direction),
    brightness(brightness)
{
}

RayTracer::Lights::DirectionalLight::DirectionalLight(
    const DirectionalLight &light
) :
    origin(light.origin),
    direction(light.direction),
    brightness(light.brightness)
{
}

RayTracer::Lights::DirectionalLight::DirectionalLight(
    DirectionalLight &&light
) :
    origin(light.origin),
    direction(light.direction),
    brightness(light.brightness)
{
}

RayTracer::Math::Point3D RayTracer::Lights::DirectionalLight::getOrigin() const
{
    return this->origin;
}

RayTracer::Math::Vector3D RayTracer::Lights::DirectionalLight::getDirection() const
{
    return this->direction;
}

double RayTracer::Lights::DirectionalLight::getBrightness() const
{
    return this->brightness;
}

RayTracer::Render::Color RayTracer::Lights::DirectionalLight::getColor() const
{
    return this->color;
}

void RayTracer::Lights::DirectionalLight::setOrigin(
    Math::Point3D origin
)
{
    this->origin = origin;
}

void RayTracer::Lights::DirectionalLight::setDirection(
    Math::Vector3D direction
)
{
    this->direction = direction;
}

void RayTracer::Lights::DirectionalLight::setBrightness(
    double brightness
)
{
    this->brightness = brightness;
}

void RayTracer::Lights::DirectionalLight::setColor(
    Render::Color color
)
{
    this->color = color;
}

extern "C" std::unique_ptr<RayTracer::Lights::DirectionalLight> createDirectionalLight(
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
