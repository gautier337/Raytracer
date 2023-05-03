/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Vector3D
*/

#include "Vector3D.hpp"
#include <iostream>
#include <cmath>
#include <array>
#include <exception>

RayTracer::Math::Vector3D::Vector3D() : x(0), y(0), z(0)
{
}

RayTracer::Math::Vector3D::~Vector3D()
{
}

RayTracer::Math::Vector3D::Vector3D(double x, double y, double z) :
    x(x),
    y(y),
    z(z)
{
}

RayTracer::Math::Vector3D::Vector3D(const RayTracer::Math::Vector3D &vector) :
    x(vector.x),
    y(vector.y),
    z(vector.z)
{
}

RayTracer::Math::Vector3D::Vector3D(RayTracer::Math::Vector3D &&vector) :
    x(vector.x),
    y(vector.y),
    z(vector.z)
{
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator=(
    const RayTracer::Math::Vector3D &vector
)
{
    this->x = vector.getX();
    this->y = vector.getY();
    this->z = vector.getZ();
    return *this;
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator=(
    RayTracer::Math::Vector3D &&vector
)
{
    this->x = vector.getX();
    this->y = vector.getY();
    this->z = vector.getZ();
    return *this;
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator+=(
    const RayTracer::Math::Vector3D &vector
)
{
    this->x += vector.getX();
    this->y += vector.getY();
    this->z += vector.getZ();
    return *this;
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator-=(
    const RayTracer::Math::Vector3D &vector
)
{
    this->x -= vector.getX();
    this->y -= vector.getY();
    this->z -= vector.getZ();
    return *this;
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator*=(
    const RayTracer::Math::Vector3D &vector
)
{
    this->x *= vector.getX();
    this->y *= vector.getY();
    this->z *= vector.getZ();
    return *this;
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator/=(
    const RayTracer::Math::Vector3D &vector
)
{
    this->x /= vector.getX();
    this->y /= vector.getY();
    this->z /= vector.getZ();
    return *this;
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator+(
    const RayTracer::Math::Vector3D &vector
)
{
    this->x += vector.getX();
    this->y += vector.getY();
    this->z += vector.getZ();
    return *this;
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator-(
    const RayTracer::Math::Vector3D &vector
)
{
    this->x -= vector.getX();
    this->y -= vector.getY();
    this->z -= vector.getZ();
    return *this;
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator*(
    const RayTracer::Math::Vector3D &vector
)
{
    this->x *= vector.getX();
    this->y *= vector.getY();
    this->z *= vector.getZ();
    return *this;
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator/(
    const RayTracer::Math::Vector3D &vector
)
{
    this->x /= vector.getX();
    this->y /= vector.getY();
    this->z /= vector.getZ();
    return *this;
}

bool &RayTracer::Math::Vector3D::operator==(const Vector3D &vector)
{
    bool *result = new bool;
    *result = this->x == vector.getX() && this->y == vector.getY() &&
        this->z == vector.getZ();
    return *result;
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator+=(double value)
{
    this->x += value;
    this->y += value;
    this->z += value;
    return *this;
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator-=(double value)
{
    this->x -= value;
    this->y -= value;
    this->z -= value;
    return *this;
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator*=(double value)
{
    this->x *= value;
    this->y *= value;
    this->z *= value;
    return *this;
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator/=(double value)
{
    this->x /= value;
    this->y /= value;
    this->z /= value;
    return *this;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator+(double value)
{
    RayTracer::Math::Vector3D vector(
        this->x + value,
        this->y + value,
        this->z + value
    );
    return vector;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator-(double value)
{
    RayTracer::Math::Vector3D vector(
        this->x - value,
        this->y - value,
        this->z - value
    );
    return vector;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator*(double value)
{
    RayTracer::Math::Vector3D vector(
        this->x * value,
        this->y * value,
        this->z * value
    );
    return vector;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator/(double value)
{
    if (value == 0)
        throw std::invalid_argument("Division by 0");

    RayTracer::Math::Vector3D vector(
        this->x / value,
        this->y / value,
        this->z / value
    );
    return vector;
}

double RayTracer::Math::Vector3D::length()
{
    return sqrt(
        pow(this->x, 2) +
        pow(this->y, 2) +
        pow(this->z, 2)
    );
}

double RayTracer::Math::Vector3D::dot(const RayTracer::Math::Vector3D &vector)
{
    return
        this->x * vector.getX() +
        this->y * vector.getY() +
        this->z * vector.getZ();
}

double RayTracer::Math::Vector3D::getX() const
{
    return this->x;
}

double RayTracer::Math::Vector3D::getY() const
{
    return this->y;
}

double RayTracer::Math::Vector3D::getZ() const
{
    return this->z;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::normalize()
{
    double length = this->length();

    RayTracer::Math::Vector3D normal(
        this->x /= length,
        this->y /= length,
        this->z /= length
    );
    return normal;
}

void RayTracer::Math::Vector3D::rotate(Math::Vector3D axis, double angle)
{
    double sinAngle = sin(-angle);
    double cosAngle = cos(-angle);

    axis.normalize();

    double x = this->x;
    double y = this->y;
    double z = this->z;

    this->x = (cosAngle + (1 - cosAngle) * pow(axis.getX(), 2)) * x;
    this->x += ((1 - cosAngle) * axis.getX() * axis.getY() - axis.getZ() * sinAngle) * y;
    this->x += ((1 - cosAngle) * axis.getX() * axis.getZ() + axis.getY() * sinAngle) * z;

    this->y = ((1 - cosAngle) * axis.getX() * axis.getY() + axis.getZ() * sinAngle) * x;
    this->y += (cosAngle + (1 - cosAngle) * pow(axis.getY(), 2)) * y;
    this->y += ((1 - cosAngle) * axis.getY() * axis.getZ() - axis.getX() * sinAngle) * z;

    this->z = ((1 - cosAngle) * axis.getX() * axis.getZ() - axis.getY() * sinAngle) * x;
    this->z += ((1 - cosAngle) * axis.getY() * axis.getZ() + axis.getX() * sinAngle) * y;
    this->z += (cosAngle + (1 - cosAngle) * pow(axis.getZ(), 2)) * z;
}
