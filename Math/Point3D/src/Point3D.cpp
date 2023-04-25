/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Point 3d
*/

#include "Point3D.hpp"
#include <cmath>

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

Math::Point3D Math::Point3D::operator+(const Math::Vector3D &vector)
{
    Math::Point3D other(this->x + vector.getX(), this->y + vector.getY(), this->z + vector.getZ());
    return other;
}

Math::Point3D &Math::Point3D::operator-=(const Math::Vector3D &vector)
{
    this->x -= vector.getX();
    this->y -= vector.getY();
    this->z -= vector.getZ();
    return *this;
}

Math::Point3D Math::Point3D::operator-(const Math::Vector3D &vector)
{
    Math::Point3D other(this->x - vector.getX(), this->y - vector.getY(), this->z - vector.getZ());
    return other;
}

Math::Point3D &Math::Point3D::operator+=(const Math::Point3D &point)
{
    this->x += point.x;
    this->y += point.y;
    this->z += point.z;
    return *this;
}

Math::Point3D Math::Point3D::operator+(const Math::Point3D &point)
{
    Math::Point3D other(this->x + point.getX(), this->y + point.getY(), this->z + point.getZ());
    return other;
}

Math::Point3D &Math::Point3D::operator-=(const Math::Point3D &point)
{
    this->x -= point.x;
    this->y -= point.y;
    this->z -= point.z;
    return *this;
}

Math::Point3D Math::Point3D::operator-(const Math::Point3D &point)
{
    Math::Point3D other(this->x - point.getX(), this->y - point.getY(), this->z - point.getZ());
    return other;
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

void Math::Point3D::setX(double x)
{
    this->x = x;
}

void Math::Point3D::setY(double y)
{
    this->y = y;
}

void Math::Point3D::setZ(double z)
{
    this->z = z;
}

double Math::Point3D::distance(const Math::Point3D &point)
{
    return sqrt(
        pow(this->x - point.getX(), 2) +
        pow(this->y - point.getY(), 2) +
        pow(this->z - point.getZ(), 2)
    );
}
