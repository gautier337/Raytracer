/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"
#include <cmath>

RayTracer::View::Camera::Camera() :
    origin(0.5, 0.5, 0),
    screen(
        RayTracer::Math::Point3D(0, 0, -1),
        RayTracer::Math::Vector3D(1, 0, 0),
        RayTracer::Math::Vector3D(0, 1, 0),
        RayTracer::Render::Color(0, 0, 0, 0)
    ),
    direction("north")
{
}

RayTracer::View::Camera::~Camera()
{
}

RayTracer::View::Camera::Camera(
    RayTracer::Math::Point3D origin,
    RayTracer::Primitives::Rectangle3D screen,
    std::string direction
) :
    origin(origin),
    screen(screen),
    direction(direction)
{
}

RayTracer::View::Camera::Camera(const Camera &camera) :
    origin(camera.origin),
    screen(camera.screen),
    direction(camera.direction)
{
}

RayTracer::View::Camera::Camera(Camera &&camera) :
    origin(camera.origin),
    screen(camera.screen),
    direction(camera.direction)
{
}

RayTracer::View::Camera &RayTracer::View::Camera::operator=(const Camera &camera)
{
    this->origin = camera.origin;
    this->screen = camera.screen;
    this->direction = camera.direction;
    return *this;
}

RayTracer::View::Camera &RayTracer::View::Camera::operator=(Camera &&camera)
{
    this->origin = camera.origin;
    this->screen = camera.screen;
    this->direction = camera.direction;
    return *this;
}

RayTracer::View::Ray RayTracer::View::Camera::ray(double u, double v)
{
    RayTracer::Math::Point3D point = this->screen.pointAt(u, v);
    RayTracer::Math::Vector3D direction(
        (point - this->origin).getX(),
        (point - this->origin).getY(),
        (point - this->origin).getZ()
    );
    return Ray(this->origin, direction);
}

void RayTracer::View::Camera::translate(RayTracer::Math::Vector3D vector)
{
    this->origin = this->origin + vector;
    this->screen.translate(vector);
}

#include <iostream>

void RayTracer::View::Camera::rotate(RayTracer::Math::Vector3D rotation, double angle)
{
    this->screen.rotate(rotation, angle);
}
