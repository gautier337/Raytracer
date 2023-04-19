/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

RayTracer::Camera::Camera() : origin(), screen()
{
}

RayTracer::Camera::~Camera()
{
}

RayTracer::Camera::Camera(Math::Point3D origin, Rectangle3D screen) : origin(origin), screen(screen)
{
}

RayTracer::Camera::Camera(const Camera &camera) : origin(camera.origin), screen(camera.screen)
{
}

RayTracer::Camera::Camera(Camera &&camera) : origin(camera.origin), screen(camera.screen)
{
}

RayTracer::Camera &RayTracer::Camera::operator=(const Camera &camera)
{
    this->origin = camera.origin;
    this->screen = camera.screen;
    return *this;
}

RayTracer::Camera &RayTracer::Camera::operator=(Camera &&camera)
{
    this->origin = camera.origin;
    this->screen = camera.screen;
    return *this;
}

RayTracer::Ray RayTracer::Camera::ray(double u, double v)
{
    Math::Point3D point = this->screen.pointAt(u, v);
    Math::Vector3D direction((point - this->origin).getX(), (point - this->origin).getY(), (point - this->origin).getZ());
    return Ray(this->origin, direction);
}
