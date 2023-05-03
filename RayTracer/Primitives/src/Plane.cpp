/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Rectangle
*/

#include "Plane.hpp"
#include <iostream>
#include <cmath>

RayTracer::Primitives::Plane::Plane() :
    axis("Z"),
    position(0),
    color(0, 0, 0, 1),
    bottom_side(1, 0, 0),
    left_side(0, 1, 0),
    origin(0, 0, 0)
{
}

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
    std::vector<std::shared_ptr<ILights>> lights
)
{
    RayTracer::Render::Color newColor(0, 0, 0, 1);
    RayTracer::Math::Point3D origin = ray.getOrigin();

    if (!this->hits(ray))
        return newColor;

    RayTracer::Math::Vector3D w(
        this->origin.getX() - ray.getOrigin().getX(),
        this->origin.getY() - ray.getOrigin().getY(),
        this->origin.getZ() - ray.getOrigin().getZ()
    );
    double a = w.dot(ray.getDirection());
    double b = ray.getDirection().dot(ray.getDirection());
    double r = a / b;

    RayTracer::Math::Point3D p = ray.getOrigin() + (ray.getDirection() * r);
    RayTracer::Math::Vector3D d(
        p.getX() - this->origin.getX(),
        p.getY() - this->origin.getY(),
        p.getZ() - this->origin.getZ()
    );

    double u = d.dot(this->bottom_side) / this->bottom_side.dot(this->bottom_side);
    double v = d.dot(this->left_side) / this->left_side.dot(this->left_side);

    double distance = p.distance(ray.getOrigin());

    double colorModifier = std::max(0.0, distance / 3000.0);
    newColor.setRGBA(
        this->color.getR() * colorModifier,
        this->color.getG() * colorModifier,
        this->color.getB() * colorModifier,
        this->color.getA()
    );

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
