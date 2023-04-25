/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** DirectionalLight.cpp
*/

#include "DirectionalLight.hpp"

RayTracer::DirectionalLight::DirectionalLight() : origin(), direction()
{
}

RayTracer::DirectionalLight::~DirectionalLight()
{
}


RayTracer::DirectionalLight::DirectionalLight(
    Math::Point3D origin,
    Math::Vector3D direction,
    double brightness
) :
    origin(origin),
    direction(direction),
    brightness(brightness)
{
}

RayTracer::DirectionalLight::DirectionalLight(const DirectionalLight &light) :
    origin(light.origin),
    direction(light.direction),
    brightness(light.brightness)
{
}

RayTracer::DirectionalLight::DirectionalLight(DirectionalLight &&light) :
    origin(light.origin),
    direction(light.direction),
    brightness(light.brightness)
{
}

RayTracer::DirectionalLight &RayTracer::DirectionalLight::operator=(const DirectionalLight &light)
{
    this->origin = light.origin;
    this->direction = light.direction;
    this->brightness = light.brightness;
    return *this;
}

RayTracer::DirectionalLight &RayTracer::DirectionalLight::operator=(DirectionalLight &&light)
{
    this->origin = light.origin;
    this->direction = light.direction;
    this->brightness = light.brightness;
    return *this;
}

Math::Point3D RayTracer::DirectionalLight::getOrigin() const
{
    return origin;
}

Math::Vector3D RayTracer::DirectionalLight::getDirection() const
{
    return direction;
}

double RayTracer::DirectionalLight::getBrightness() const
{
    return brightness;
}
