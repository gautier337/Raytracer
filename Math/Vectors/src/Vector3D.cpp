/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Vector3D
*/

#include "Vector3D.hpp"
#include <iostream>

Math::Vector3D::Vector3D() : x(0), y(0), z(0)
{
    std::cout << "Vector3D created" << std::endl;
}

Math::Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z)
{
    std::cout << "Vector3D created" << std::endl;
    std::cout << "  - y: " << y << std::endl;
    std::cout << "  - x: " << x << std::endl;
    std::cout << "  - z: " << z << std::endl;
}

Math::Vector3D::~Vector3D()
{
}

double Math::Vector3D::length()
{
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}
