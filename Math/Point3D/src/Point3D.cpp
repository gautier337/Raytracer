/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Point 3d
*/

#include "Point3D.hpp"

Math::Point3D::Point3D() : x(0), y(0), z(0)
{
}

Math::Point3D::~Point3D()
{
}

Math::Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z)
{
}

Math::Point3D::Point3D(const Math::Point3D &point) : x(point.x), y(point.y), z(point.z)
{
}

Math::Point3D::Point3D(Math::Point3D &&point) : x(point.x), y(point.y), z(point.z)
{
}

Math::Point3D &Math::Point3D::operator=(const Math::Point3D &point)
{
    this->x = point.x;
    this->y = point.y;
    this->z = point.z;
    return *this;
}

Math::Point3D &Math::Point3D::operator=(Math::Point3D &&point)
{
    this->x = point.x;
    this->y = point.y;
    this->z = point.z;
    return *this;
}

Math::Point3D &Math::Point3D::operator+=(const Math::Vector3D &vector)
{
    this->x += vector.getX();
    this->y += vector.getY();
    this->z += vector.getZ();
    return *this;
}

Math::Point3D &Math::Point3D::operator+(const Math::Vector3D &vector)
{
    return *this += vector;
}

Math::Point3D &Math::Point3D::operator-=(const Math::Point3D &point)
{
    this->x -= point.x;
    this->y -= point.y;
    this->z -= point.z;
    return *this;
}

Math::Point3D &Math::Point3D::operator-(const Math::Point3D &point)
{
    return *this -= point;
}

double Math::Point3D::getX() const
{
    return this->x;
}

double Math::Point3D::getY() const
{
    return this->y;
}

double Math::Point3D::getZ() const
{
    return this->z;
}
