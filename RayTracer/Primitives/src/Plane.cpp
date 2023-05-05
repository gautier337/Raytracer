/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Rectangle
*/

#include "Plane.hpp"
#include <iostream>
#include <cmath>

RayTracer::Primitives::Plane::~Plane()
{
}

RayTracer::Primitives::Plane::Plane(
    std::string axis,
    double position,
    RayTracer::Render::Color color
) :
    axis(axis),
    position(position),
    color(color)
{
    if (this->axis == "X") {
        this->bottom_side = Math::Vector3D(10000, 0, 0);
        this->left_side = Math::Vector3D(0, 0, 10000);
        this->origin = Math::Point3D(0, 0, this->position);
    } else if (this->axis == "Y") {
        this->bottom_side = Math::Vector3D(10000, 0, 0);
        this->left_side = Math::Vector3D(0, 0, 10000);
        this->origin = Math::Point3D(this->position, 0, 0);
    } else if (this->axis == "Z") {
        this->bottom_side = Math::Vector3D(0, 10000, 10000);
        this->left_side = Math::Vector3D(0, 0, 0);
        this->origin = Math::Point3D(0, this->position, 0);
    }
}

RayTracer::Primitives::Plane::Plane(
    const RayTracer::Primitives::Plane &rectangle
) :
    axis(rectangle.axis),
    position(rectangle.position),
    color(rectangle.color),
    bottom_side(rectangle.bottom_side),
    left_side(rectangle.left_side),
    origin(rectangle.origin)
{
}

RayTracer::Primitives::Plane::Plane(
    RayTracer::Primitives::Plane &&rectangle
) :
    axis(rectangle.axis),
    position(rectangle.position),
    color(rectangle.color),
    bottom_side(rectangle.bottom_side),
    left_side(rectangle.left_side),
    origin(rectangle.origin)
{
}

RayTracer::Primitives::Plane &RayTracer::Primitives::Plane::operator=(
    const Plane &rectangle
)
{
    this->axis = rectangle.axis;
    this->position = rectangle.position;
    this->color = rectangle.color;
    this->bottom_side = rectangle.bottom_side;
    this->left_side = rectangle.left_side;
    this->origin = rectangle.origin;
    return *this;
}

RayTracer::Primitives::Plane &RayTracer::Primitives::Plane::operator=(
    Plane &&rectangle
)
{
    this->axis = rectangle.axis;
    this->position = rectangle.position;
    this->color = rectangle.color;
    this->bottom_side = rectangle.bottom_side;
    this->left_side = rectangle.left_side;
    this->origin = rectangle.origin;
    return *this;
}

double RayTracer::Primitives::Plane::getIntersectionPoint(View::Ray ray)
{
    RayTracer::Math::Vector3D w(
        this->origin.getX() - ray.getOrigin().getX(),
        this->origin.getY() - ray.getOrigin().getY(),
        this->origin.getZ() - ray.getOrigin().getZ()
    );
    double a = w.dot(ray.getDirection());
    double b = ray.getDirection().dot(ray.getDirection());
    double r = a / b;

    if (r < 0)
        return -1;

    RayTracer::Math::Point3D p = ray.getOrigin() + (ray.getDirection() * r);
    RayTracer::Math::Vector3D d(
        p.getX() - this->origin.getX(),
        p.getY() - this->origin.getY(),
        p.getZ() - this->origin.getZ()
    );

    double ddota = d.dot(this->bottom_side);
    if (ddota < 0 || ddota > this->bottom_side.dot(this->bottom_side))
        return -1;

    double ddotb = d.dot(this->left_side);
    if (ddotb < 0 || ddotb > this->left_side.dot(this->left_side))
        return -1;

    return r;
}

bool RayTracer::Primitives::Plane::hits(const RayTracer::View::Ray ray)
{
    RayTracer::Math::Vector3D w(
        this->origin.getX() - ray.getOrigin().getX(),
        this->origin.getY() - ray.getOrigin().getY(),
        this->origin.getZ() - ray.getOrigin().getZ()
    );
    double a = w.dot(ray.getDirection());
    double b = ray.getDirection().dot(ray.getDirection());
    double r = a / b;

    if (r < 0)
        return false;

    RayTracer::Math::Point3D p = ray.getOrigin() + (ray.getDirection() * r);
    RayTracer::Math::Vector3D d(
        p.getX() - this->origin.getX(),
        p.getY() - this->origin.getY(),
        p.getZ() - this->origin.getZ()
    );

    double ddota = d.dot(this->bottom_side);
    if (ddota < 0 || ddota > this->bottom_side.dot(this->bottom_side))
        return false;

    double ddotb = d.dot(this->left_side);
    if (ddotb < 0 || ddotb > this->left_side.dot(this->left_side))
        return false;

    return true;
}

RayTracer::Render::Color RayTracer::Primitives::Plane::computeColor(
    RayTracer::View::Ray ray,
    std::vector<std::unique_ptr<ILights>> &lights
)
{
    RayTracer::Render::Color newColor(0, 0, 0, 1);
    RayTracer::Math::Point3D origin = ray.getOrigin();

    if (!this->hits(ray))
        return newColor;

    RayTracer::Math::Vector3D normal = this->bottom_side.cross(this->left_side);
    normal.normalize();

    for (const auto &light : lights) {
        if (light->getDirection() == RayTracer::Math::Vector3D(0, 0, 0)) {
            RayTracer::Render::Color lightColor(
                this->color.getR() * light->getBrightness(),
                this->color.getG() * light->getBrightness(),
                this->color.getB() * light->getBrightness(),
                this->color.getA()
            );
            newColor += lightColor;
        }
        RayTracer::Math::Vector3D lightDir = light->getDirection().normalize();
        double dot = std::max(0.0, normal.dot(lightDir));
        double brightness = light->getBrightness();
        RayTracer::Render::Color lightColor(
            this->color.getR() * dot * brightness,
            this->color.getG() * dot * brightness,
            this->color.getB() * dot * brightness,
            this->color.getA()
        );
        newColor += lightColor;
    }
    return newColor;
}

RayTracer::Math::Point3D RayTracer::Primitives::Plane::pointAt(
    double u,
    double v
)
{
    if (u < 0 || u > 1 || v < 0 || v > 1)
        throw std::invalid_argument("u and v must be between 0 and 1");

    return this->origin + (this->bottom_side * u) + (this->left_side * v);
}

void RayTracer::Primitives::Plane::translate(
    RayTracer::Math::Vector3D translation
)
{
    return;
}

void RayTracer::Primitives::Plane::rotate(RayTracer::Math::Vector3D rotation, double angle)
{
    return;
}

void RayTracer::Primitives::Plane::scale(double factor)
{
    return;
}

std::string RayTracer::Primitives::Plane::getType() const {
    return "Plane";
}

RayTracer::Render::Color RayTracer::Primitives::Plane::getColor() const {
    return this->color;
}

extern "C" std::unique_ptr<RayTracer::Primitives::Plane> createPlane(
    std::string axis,
    double position,
    RayTracer::Render::Color color
)
{
    return std::make_unique<RayTracer::Primitives::Plane>(
        axis,
        position,
        color
    );
}
