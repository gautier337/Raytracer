/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Vector
*/

#include "Vector3D.hpp"
#include <iostream>
#include <cmath>
#include <array>
#include <exception>

Math::Vector3D::Vector3D() : x(0), y(0), z(0)
{
}

Math::Vector3D::~Vector3D()
{
}

Math::Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z)
{
}

Math::Vector3D::Vector3D(const Math::Vector3D &vector) : x(vector.x), y(vector.y), z(vector.z)
{
}

Math::Vector3D::Vector3D(Math::Vector3D &&vector) : x(vector.x), y(vector.y), z(vector.z)
{
}

Math::Vector3D &Math::Vector3D::operator=(const Math::Vector3D &vector)
{
    this->x = vector.getX();
    this->y = vector.getY();
    this->z = vector.getZ();
    return *this;
}

Math::Vector3D &Math::Vector3D::operator=(Math::Vector3D &&vector)
{
    this->x = vector.getX();
    this->y = vector.getY();
    this->z = vector.getZ();
    return *this;
}

Math::Vector3D &Math::Vector3D::operator+=(const Math::Vector3D &vector)
{
    this->x += vector.getX();
    this->y += vector.getY();
    this->z += vector.getZ();
    return *this;
}

Math::Vector3D &Math::Vector3D::operator-=(const Math::Vector3D &vector)
{
    this->x -= vector.getX();
    this->y -= vector.getY();
    this->z -= vector.getZ();
    return *this;
}

Math::Vector3D &Math::Vector3D::operator*=(const Math::Vector3D &vector)
{
    this->x *= vector.getX();
    this->y *= vector.getY();
    this->z *= vector.getZ();
    return *this;
}

Math::Vector3D &Math::Vector3D::operator/=(const Math::Vector3D &vector)
{
    this->x /= vector.getX();
    this->y /= vector.getY();
    this->z /= vector.getZ();
    return *this;
}

Math::Vector3D &Math::Vector3D::operator+(const Math::Vector3D &vector)
{
    this->x += vector.getX();
    this->y += vector.getY();
    this->z += vector.getZ();
    return *this;
}

Math::Vector3D &Math::Vector3D::operator-(const Math::Vector3D &vector)
{
    this->x -= vector.getX();
    this->y -= vector.getY();
    this->z -= vector.getZ();
    return *this;
}

Math::Vector3D &Math::Vector3D::operator*(const Math::Vector3D &vector)
{
    this->x *= vector.getX();
    this->y *= vector.getY();
    this->z *= vector.getZ();
    return *this;
}

Math::Vector3D &Math::Vector3D::operator/(const Math::Vector3D &vector)
{
    this->x /= vector.getX();
    this->y /= vector.getY();
    this->z /= vector.getZ();
    return *this;
}

Math::Vector3D &Math::Vector3D::operator+=(double value)
{
    this->x += value;
    this->y += value;
    this->z += value;
    return *this;
}

Math::Vector3D &Math::Vector3D::operator-=(double value)
{
    this->x -= value;
    this->y -= value;
    this->z -= value;
    return *this;
}

Math::Vector3D &Math::Vector3D::operator*=(double value)
{
    this->x *= value;
    this->y *= value;
    this->z *= value;
    return *this;
}

Math::Vector3D &Math::Vector3D::operator/=(double value)
{
    this->x /= value;
    this->y /= value;
    this->z /= value;
    return *this;
}

Math::Vector3D Math::Vector3D::operator+(double value)
{
    Math::Vector3D vector(this->x + value, this->y + value, this->z + value);
    return vector;
}

Math::Vector3D Math::Vector3D::operator-(double value)
{
    Math::Vector3D vector(this->x - value, this->y - value, this->z - value);
    return vector;
}

Math::Vector3D Math::Vector3D::operator*(double value)
{
    Math::Vector3D vector(this->x * value, this->y * value, this->z * value);
    return vector;
}

Math::Vector3D Math::Vector3D::operator/(double value)
{
    if (value == 0)
        throw std::invalid_argument("Division by 0");

    Math::Vector3D vector(this->x / value, this->y / value, this->z / value);
    return vector;
}

double Math::Vector3D::length()
{
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

double Math::Vector3D::dot(const Math::Vector3D &vector)
{
    return this->x * vector.getX() + this->y * vector.getY() + this->z * vector.getZ();
}

double Math::Vector3D::getX() const
{
    return this->x;
}

double Math::Vector3D::getY() const
{
    return this->y;
}

double Math::Vector3D::getZ() const
{
    return this->z;
}
