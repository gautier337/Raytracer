/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Rectangle
*/

#include "Rectangle3D.hpp"
#include <iostream>
#include <cmath>

RayTracer::Rectangle3D::Rectangle3D() :
    origin(0, 0, 0),
    bottom_side(1, 0, 0),
    left_side(0, 1, 0),
    color(0, 0, 0, 1)
{
}

RayTracer::Rectangle3D::~Rectangle3D()
{
}

RayTracer::Rectangle3D::Rectangle3D(
    Math::Point3D origin,
    Math::Vector3D bottom_side,
    Math::Vector3D left_side,
    RayTracer::Color color
) :
    origin(origin),
    bottom_side(bottom_side),
    left_side(left_side),
    color(color)
{
}

RayTracer::Rectangle3D::Rectangle3D(const Rectangle3D &rectangle) :
    origin(rectangle.origin),
    bottom_side(rectangle.bottom_side),
    left_side(rectangle.left_side),
    color(rectangle.color)
{
}

RayTracer::Rectangle3D::Rectangle3D(Rectangle3D &&rectangle) :
    origin(rectangle.origin),
    bottom_side(rectangle.bottom_side),
    left_side(rectangle.left_side),
    color(rectangle.color)
{
}

RayTracer::Rectangle3D &RayTracer::Rectangle3D::operator=(const Rectangle3D &rectangle)
{
    this->origin = rectangle.origin;
    this->bottom_side = rectangle.bottom_side;
    this->left_side = rectangle.left_side;
    this->color = rectangle.color;
    return *this;
}

RayTracer::Rectangle3D &RayTracer::Rectangle3D::operator=(Rectangle3D &&rectangle)
{
    this->origin = rectangle.origin;
    this->bottom_side = rectangle.bottom_side;
    this->left_side = rectangle.left_side;
    this->color = rectangle.color;
    return *this;
}

bool RayTracer::Rectangle3D::hits(const Ray ray)
{
    Math::Vector3D w(
        this->origin.getX() - ray.getOrigin().getX(),
        this->origin.getY() - ray.getOrigin().getY(),
        this->origin.getZ() - ray.getOrigin().getZ()
    );
    double a = w.dot(ray.getDirection());
    double b = ray.getDirection().dot(ray.getDirection());
    double r = a / b;

    if (r < 0)
        return false;

    Math::Point3D p = ray.getOrigin() + (ray.getDirection() * r);
    Math::Vector3D d(
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

RayTracer::Color RayTracer::Rectangle3D::computeColor(Ray ray)
{
    RayTracer::Color newColor(0, 0, 0, 1);
    Math::Point3D origin = ray.getOrigin();

    if (!this->hits(ray))
        return newColor;

    Math::Vector3D w(
        this->origin.getX() - ray.getOrigin().getX(),
        this->origin.getY() - ray.getOrigin().getY(),
        this->origin.getZ() - ray.getOrigin().getZ()
    );
    double a = w.dot(ray.getDirection());
    double b = ray.getDirection().dot(ray.getDirection());
    double r = a / b;

    Math::Point3D p = ray.getOrigin() + (ray.getDirection() * r);
    Math::Vector3D d(
        p.getX() - this->origin.getX(),
        p.getY() - this->origin.getY(),
        p.getZ() - this->origin.getZ()
    );

    double u = d.dot(this->bottom_side) / this->bottom_side.dot(this->bottom_side);
    double v = d.dot(this->left_side) / this->left_side.dot(this->left_side);
    double distance = sqrt(
        (origin.getX() - p.getX()) * (origin.getX() - p.getX()) +
        (origin.getY() - p.getY()) * (origin.getY() - p.getY()) +
        (origin.getZ() - p.getZ()) * (origin.getZ() - p.getZ())
    );

    newColor.setRGBA(
        this->color.getR() * distance,
        this->color.getG() * distance,
        this->color.getB() * distance,
        this->color.getA() * 1
    );
    return newColor;
}

Math::Point3D RayTracer::Rectangle3D::pointAt(double u, double v)
{
    if (u < 0 || u > 1 || v < 0 || v > 1)
        throw std::invalid_argument("u and v must be between 0 and 1");

    return this->origin + (this->bottom_side * u) + (this->left_side * v);
}

void RayTracer::Rectangle3D::translate(Math::Vector3D translation)
{
    this->origin = this->origin + translation;
}
