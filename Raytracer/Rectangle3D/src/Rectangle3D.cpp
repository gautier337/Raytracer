/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Rectangle
*/

#include "Rectangle3D.hpp"

RayTracer::Rectangle3D::Rectangle3D() : origin(), bottom_side(), left_side()
{
}

RayTracer::Rectangle3D::~Rectangle3D()
{
}

RayTracer::Rectangle3D::Rectangle3D(Math::Point3D origin, Math::Vector3D bottom_side, Math::Vector3D left_side) : origin(origin), bottom_side(bottom_side), left_side(left_side)
{
}

RayTracer::Rectangle3D::Rectangle3D(const Rectangle3D &rectangle) : origin(rectangle.origin), bottom_side(rectangle.bottom_side), left_side(rectangle.left_side)
{
}

RayTracer::Rectangle3D::Rectangle3D(Rectangle3D &&rectangle) : origin(rectangle.origin), bottom_side(rectangle.bottom_side), left_side(rectangle.left_side)
{
}

RayTracer::Rectangle3D &RayTracer::Rectangle3D::operator=(const Rectangle3D &rectangle)
{
    this->origin = rectangle.origin;
    this->bottom_side = rectangle.bottom_side;
    this->left_side = rectangle.left_side;
    return *this;
}

RayTracer::Rectangle3D &RayTracer::Rectangle3D::operator=(Rectangle3D &&rectangle)
{
    this->origin = rectangle.origin;
    this->bottom_side = rectangle.bottom_side;
    this->left_side = rectangle.left_side;
    return *this;
}

Math::Point3D RayTracer::Rectangle3D::pointAt(double u, double v)
{
    if (u < 0 || u > 1 || v < 0 || v > 1)
        return Math::Point3D();
        //throw std::invalid_argument("u and v must be between 0 and 1");
    return this->origin + (this->bottom_side * u) + (this->left_side * v);
}