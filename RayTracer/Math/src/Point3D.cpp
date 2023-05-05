/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Point3D
*/

#include "Point3D.hpp"
#include <cmath>
#include <memory>

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

void RayTracer::Math::Point3D::rotate(Math::Vector3D axis, double angle)
{
    double x = this->x;
    double y = this->y;
    double z = this->z;
    double u = axis.getX();
    double v = axis.getY();
    double w = axis.getZ();
    double cosT = cos(angle);
    double sinT = sin(angle);
    double msinT = 1 - cosT;
    double l = sqrt(u * u + v * v + w * w);
    u /= l;
    v /= l;
    w /= l;
    this->x = (u * u * msinT + cosT) * x + (u * v * msinT - w * sinT) * y +
        (u * w * msinT + v * sinT) * z;
    this->y = (u * v * msinT + w * sinT) * x + (v * v * msinT + cosT) * y +
        (v * w * msinT - u * sinT) * z;
    this->z = (u * w * msinT - v * sinT) * x + (v * w * msinT + u * sinT) * y +
        (w * w * msinT + cosT) * z;
}

extern "C" std::unique_ptr<RayTracer::Math::Point3D> createPoint3D(
    double x,
    double y,
    double z
)
{
    return std::make_unique<RayTracer::Math::Point3D>(x, y, z);
}
