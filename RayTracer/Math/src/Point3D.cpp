/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Point3D
*/

#include "Point3D.hpp"
#include <cmath>

RayTracer::Math::Point3D::Point3D() :
    x(0),
    y(0),
    z(0)
{
}

RayTracer::Math::Point3D::~Point3D()
{
}

RayTracer::Math::Point3D::Point3D(
    double x,
    double y,
    double z
) :
    x(x),
    y(y),
    z(z)
{
}

RayTracer::Math::Point3D::Point3D(const RayTracer::Math::Point3D &point) :
    x(point.x),
    y(point.y),
    z(point.z)
{
}

RayTracer::Math::Point3D::Point3D(RayTracer::Math::Point3D &&point) :
    x(point.x),
    y(point.y),
    z(point.z)
{
}

RayTracer::Math::Point3D &RayTracer::Math::Point3D::operator=(
    const RayTracer::Math::Point3D &point
)
{
    this->x = point.x;
    this->y = point.y;
    this->z = point.z;
    return *this;
}

RayTracer::Math::Point3D &RayTracer::Math::Point3D::operator=(
    RayTracer::Math::Point3D &&point
)
{
    this->x = point.x;
    this->y = point.y;
    this->z = point.z;
    return *this;
}

RayTracer::Math::Point3D &RayTracer::Math::Point3D::operator+=(
    const RayTracer::Math::Vector3D &vector
)
{
    this->x += vector.getX();
    this->y += vector.getY();
    this->z += vector.getZ();
    return *this;
}

RayTracer::Math::Point3D RayTracer::Math::Point3D::operator+(
    const RayTracer::Math::Vector3D &vector
)
{
    RayTracer::Math::Point3D other(
        this->x + vector.getX(),
        this->y + vector.getY(),
        this->z + vector.getZ()
    );
    return other;
}

RayTracer::Math::Point3D &RayTracer::Math::Point3D::operator-=(
    const RayTracer::Math::Vector3D &vector
)
{
    this->x -= vector.getX();
    this->y -= vector.getY();
    this->z -= vector.getZ();
    return *this;
}

RayTracer::Math::Point3D RayTracer::Math::Point3D::operator-(
    const RayTracer::Math::Vector3D &vector
)
{
    RayTracer::Math::Point3D other(
        this->x - vector.getX(),
        this->y - vector.getY(),
        this->z - vector.getZ()
    );
    return other;
}

RayTracer::Math::Point3D &RayTracer::Math::Point3D::operator+=(
    const RayTracer::Math::Point3D &point
)
{
    this->x += point.x;
    this->y += point.y;
    this->z += point.z;
    return *this;
}

RayTracer::Math::Point3D RayTracer::Math::Point3D::operator+(
    const RayTracer::Math::Point3D &point
)
{
    RayTracer::Math::Point3D other(
        this->x + point.getX(),
        this->y + point.getY(),
        this->z + point.getZ()
    );
    return other;
}

RayTracer::Math::Point3D &RayTracer::Math::Point3D::operator-=(
    const RayTracer::Math::Point3D &point
)
{
    this->x -= point.x;
    this->y -= point.y;
    this->z -= point.z;
    return *this;
}

RayTracer::Math::Point3D RayTracer::Math::Point3D::operator-(
    const RayTracer::Math::Point3D &point
)
{
    RayTracer::Math::Point3D other(
        this->x - point.getX(),
        this->y - point.getY(),
        this->z - point.getZ()
    );
    return other;
}

double RayTracer::Math::Point3D::getX() const
{
    return this->x;
}

double RayTracer::Math::Point3D::getY() const
{
    return this->y;
}

double RayTracer::Math::Point3D::getZ() const
{
    return this->z;
}

void RayTracer::Math::Point3D::setX(double x)
{
    this->x = x;
}

void RayTracer::Math::Point3D::setY(double y)
{
    this->y = y;
}

void RayTracer::Math::Point3D::setZ(double z)
{
    this->z = z;
}

double RayTracer::Math::Point3D::distance(const RayTracer::Math::Point3D &point)
{
    return sqrt(
        pow(this->x - point.getX(), 2) +
        pow(this->y - point.getY(), 2) +
        pow(this->z - point.getZ(), 2)
    );
}
