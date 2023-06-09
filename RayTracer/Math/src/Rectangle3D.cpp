/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Rectangle
*/

#include "Rectangle3D.hpp"
#include <iostream>
#include <cmath>
#include <memory>

RayTracer::Math::Rectangle3D::~Rectangle3D()
{
}

RayTracer::Math::Rectangle3D::Rectangle3D(
    RayTracer::Math::Point3D origin,
    RayTracer::Math::Vector3D bottom_side,
    RayTracer::Math::Vector3D left_side
) :
    origin(origin),
    bottom_side(bottom_side),
    left_side(left_side)
{
}

RayTracer::Math::Rectangle3D::Rectangle3D(
    const RayTracer::Math::Rectangle3D &rectangle
) :
    origin(rectangle.origin),
    bottom_side(rectangle.bottom_side),
    left_side(rectangle.left_side)
{
}

RayTracer::Math::Rectangle3D::Rectangle3D(
    RayTracer::Math::Rectangle3D &&rectangle
) :
    origin(rectangle.origin),
    bottom_side(rectangle.bottom_side),
    left_side(rectangle.left_side)
{
}

RayTracer::Math::Rectangle3D &RayTracer::Math::Rectangle3D::operator=(
    const Rectangle3D &rectangle
)
{
    this->origin = rectangle.origin;
    this->bottom_side = rectangle.bottom_side;
    this->left_side = rectangle.left_side;
    return *this;
}

RayTracer::Math::Rectangle3D &RayTracer::Math::Rectangle3D::operator=(
    Rectangle3D &&rectangle
)
{
    this->origin = rectangle.origin;
    this->bottom_side = rectangle.bottom_side;
    this->left_side = rectangle.left_side;
    return *this;
}

RayTracer::Math::Point3D RayTracer::Math::Rectangle3D::pointAt(
    double u,
    double v
)
{
    if (u < 0 || u > 1 || v < 0 || v > 1)
        throw std::invalid_argument("u and v must be between 0 and 1");

    return this->origin + (this->bottom_side * u) + (this->left_side * v);
}

void RayTracer::Math::Rectangle3D::translate(
    RayTracer::Math::Vector3D translation
)
{
    this->origin = this->origin + translation;
}

void RayTracer::Math::Rectangle3D::rotate(RayTracer::Math::Vector3D rotation, double angle)
{
    this->origin.rotate(rotation, angle);
    this->bottom_side.rotate(rotation, angle);
    this->left_side.rotate(rotation, angle);
}

void RayTracer::Math::Rectangle3D::scale(double factor)
{
    this->bottom_side = this->bottom_side * factor;
    this->left_side = this->left_side * factor;
}

extern "C" std::unique_ptr<RayTracer::Math::Rectangle3D> createRectangle3D(
    RayTracer::Math::Point3D origin,
    RayTracer::Math::Vector3D bottom_side,
    RayTracer::Math::Vector3D left_side
)
{
    return std::make_unique<RayTracer::Math::Rectangle3D>(
        origin,
        bottom_side,
        left_side
    );
}
