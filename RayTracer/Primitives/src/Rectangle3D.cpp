/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Rectangle
*/

#include "Rectangle3D.hpp"
#include <iostream>
#include <cmath>

RayTracer::Primitives::Rectangle3D::Rectangle3D() :
    origin(0, 0, 0),
    bottom_side(1, 0, 0),
    left_side(0, 1, 0),
    color(0, 0, 0, 1)
{
}

RayTracer::Primitives::Rectangle3D::~Rectangle3D()
{
}

RayTracer::Primitives::Rectangle3D::Rectangle3D(
    RayTracer::Math::Point3D origin,
    RayTracer::Math::Vector3D bottom_side,
    RayTracer::Math::Vector3D left_side,
    RayTracer::Render::Color color
) :
    origin(origin),
    bottom_side(bottom_side),
    left_side(left_side),
    color(color)
{
}

RayTracer::Primitives::Rectangle3D::Rectangle3D(
    const RayTracer::Primitives::Rectangle3D &rectangle
) :
    origin(rectangle.origin),
    bottom_side(rectangle.bottom_side),
    left_side(rectangle.left_side),
    color(rectangle.color)
{
}

RayTracer::Primitives::Rectangle3D::Rectangle3D(
    RayTracer::Primitives::Rectangle3D &&rectangle
) :
    origin(rectangle.origin),
    bottom_side(rectangle.bottom_side),
    left_side(rectangle.left_side),
    color(rectangle.color)
{
}

RayTracer::Primitives::Rectangle3D &RayTracer::Primitives::Rectangle3D::operator=(
    const Rectangle3D &rectangle
)
{
    this->origin = rectangle.origin;
    this->bottom_side = rectangle.bottom_side;
    this->left_side = rectangle.left_side;
    this->color = rectangle.color;
    return *this;
}

RayTracer::Primitives::Rectangle3D &RayTracer::Primitives::Rectangle3D::operator=(
    Rectangle3D &&rectangle
)
{
    this->origin = rectangle.origin;
    this->bottom_side = rectangle.bottom_side;
    this->left_side = rectangle.left_side;
    this->color = rectangle.color;
    return *this;
}

double RayTracer::Primitives::Rectangle3D::getIntersectionPoint(View::Ray ray)
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

bool RayTracer::Primitives::Rectangle3D::hits(const RayTracer::View::Ray ray)
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

RayTracer::Render::Color RayTracer::Primitives::Rectangle3D::computeColor(
    RayTracer::View::Ray ray,
    std::vector<std::unique_ptr<ILights>> &lights
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

    double colorModifier = std::max(0.0, distance / 3000);
    newColor.setRGBA(
        this->color.getR() * colorModifier,
        this->color.getG() * colorModifier,
        this->color.getB() * colorModifier,
        this->color.getA()
    );

    return newColor;
}

RayTracer::Math::Point3D RayTracer::Primitives::Rectangle3D::pointAt(
    double u,
    double v
)
{
    if (u < 0 || u > 1 || v < 0 || v > 1)
        throw std::invalid_argument("u and v must be between 0 and 1");

    return this->origin + (this->bottom_side * u) + (this->left_side * v);
}

void RayTracer::Primitives::Rectangle3D::translate(
    RayTracer::Math::Vector3D translation
)
{
    this->origin = this->origin + translation;
}

void RayTracer::Primitives::Rectangle3D::rotate(RayTracer::Math::Vector3D rotation, double angle)
{
    this->origin.rotate(rotation, angle);
    this->bottom_side.rotate(rotation, angle);
    this->left_side.rotate(rotation, angle);
}
