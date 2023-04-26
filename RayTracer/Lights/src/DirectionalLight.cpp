/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** DirectionalLight.cpp
*/

#include "DirectionalLight.hpp"

RayTracer::Lights::DirectionalLight::DirectionalLight() : origin(), direction()
{
}

RayTracer::Lights::DirectionalLight::~DirectionalLight()
{
}


RayTracer::Lights::DirectionalLight::DirectionalLight(
    Math::Point3D origin,
    Math::Vector3D direction,
    double brightness
) :
    origin(origin),
    direction(direction),
    brightness(brightness)
{
}

RayTracer::Lights::DirectionalLight::DirectionalLight(const DirectionalLight &light) :
    origin(light.origin),
    direction(light.direction),
    brightness(light.brightness)
{
}

RayTracer::Lights::DirectionalLight::DirectionalLight(DirectionalLight &&light) :
    origin(light.origin),
    direction(light.direction),
    brightness(light.brightness)
{
}

RayTracer::Lights::DirectionalLight &RayTracer::Lights::DirectionalLight::operator=(
    const DirectionalLight &light
)
{
    this->origin = light.origin;
    this->direction = light.direction;
    this->brightness = light.brightness;
    return *this;
}

RayTracer::Lights::DirectionalLight &RayTracer::Lights::DirectionalLight::operator=(
    DirectionalLight &&light
)
{
    this->origin = light.origin;
    this->direction = light.direction;
    this->brightness = light.brightness;
    return *this;
}

RayTracer::Math::Point3D RayTracer::Lights::DirectionalLight::getOrigin() const
{
    return origin;
}

RayTracer::Math::Vector3D RayTracer::Lights::DirectionalLight::getDirection() const
{
    return direction;
}

double RayTracer::Lights::DirectionalLight::getBrightness() const
{
    return brightness;
}
