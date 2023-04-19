/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Ray.cpp
*/

#include "Ray.hpp"

RayTracer::Ray::Ray() : origin(), direction()
{
}

RayTracer::Ray::~Ray()
{
}


RayTracer::Ray::Ray(Math::Point3D origin, Math::Vector3D direction) : origin(origin), direction(direction)
{
}

RayTracer::Ray::Ray(const Ray &ray) : origin(ray.origin), direction(ray.direction)
{
}

RayTracer::Ray::Ray(Ray &&ray) : origin(ray.origin), direction(ray.direction)
{
}

RayTracer::Ray &RayTracer::Ray::operator=(const Ray &ray)
{
    this->origin = ray.origin;
    this->direction = ray.direction;
    return *this;
}

RayTracer::Ray &RayTracer::Ray::operator=(Ray &&ray)
{
    this->origin = ray.origin;
    this->direction = ray.direction;
    return *this;
}

Math::Point3D RayTracer::Ray::getOrigin() const
{
    return this->origin;
}

Math::Vector3D RayTracer::Ray::getDirection() const
{
    return this->direction;
}