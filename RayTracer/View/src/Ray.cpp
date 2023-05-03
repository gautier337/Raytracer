/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Ray
*/

#include "Ray.hpp"
#include <memory>

RayTracer::View::Ray::Ray() :
    origin(),
    direction()
{
}

RayTracer::View::Ray::~Ray()
{
}


RayTracer::View::Ray::Ray(
    Math::Point3D origin,
    Math::Vector3D direction
) :
    origin(origin),
    direction(direction)
{
}

RayTracer::View::Ray::Ray(const Ray &ray) :
    origin(ray.origin),
    direction(ray.direction)
{
}

RayTracer::View::Ray::Ray(Ray &&ray) :
    origin(ray.origin),
    direction(ray.direction)
{
}

RayTracer::View::Ray &RayTracer::View::Ray::operator=(const Ray &ray)
{
    this->origin = ray.origin;
    this->direction = ray.direction;
    return *this;
}

RayTracer::View::Ray &RayTracer::View::Ray::operator=(Ray &&ray)
{
    this->origin = ray.origin;
    this->direction = ray.direction;
    return *this;
}

RayTracer::Math::Point3D RayTracer::View::Ray::getOrigin() const
{
    return this->origin;
}

RayTracer::Math::Vector3D RayTracer::View::Ray::getDirection() const
{
    return this->direction;
}

extern "C" std::unique_ptr<RayTracer::View::Ray> createRay(
    RayTracer::Math::Point3D origin,
    RayTracer::Math::Vector3D direction
)
{
    return std::make_unique<RayTracer::View::Ray>(origin, direction);
}
