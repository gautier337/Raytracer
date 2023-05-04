/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** AmbientLight.cpp
*/

#include "AmbientLight.hpp"

RayTracer::Lights::AmbientLight::AmbientLight() :
    brightness(0),
    color(0, 0, 0, 1)
{
}

RayTracer::Lights::AmbientLight::~AmbientLight()
{
}


RayTracer::Lights::AmbientLight::AmbientLight(
    double brightness,
    Render::Color color
) :
    brightness(brightness),
    color(color)
{
}

RayTracer::Lights::AmbientLight::AmbientLight(
    const AmbientLight &light
) :
    brightness(light.brightness),
    color(light.color)
{
}

RayTracer::Lights::AmbientLight::AmbientLight(
    AmbientLight &&light
) :
    brightness(light.brightness),
    color(light.color)
{
}

RayTracer::Math::Point3D RayTracer::Lights::AmbientLight::getOrigin() const
{
    return Math::Point3D(0, 0, 0);
}

RayTracer::Math::Vector3D RayTracer::Lights::AmbientLight::getDirection() const
{
    return Math::Vector3D(0, 0, 0);
}

double RayTracer::Lights::AmbientLight::getBrightness() const
{
    return this->brightness;
}

RayTracer::Render::Color RayTracer::Lights::AmbientLight::getColor() const
{
    return this->color;
}

void RayTracer::Lights::AmbientLight::setOrigin(
    Math::Point3D origin
)
{
    return;
}

void RayTracer::Lights::AmbientLight::setDirection(
    Math::Vector3D direction
)
{
    return;
}

void RayTracer::Lights::AmbientLight::setBrightness(
    double brightness
)
{
    this->brightness = brightness;
}

void RayTracer::Lights::AmbientLight::setColor(
    Render::Color color
)
{
    this->color = color;
}
