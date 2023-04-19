/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Factory
*/

#include "Factory.hpp"
#include "Vector3D.hpp"

Math::Factory::~Factory()
{
}

std::unique_ptr<Math::Vector3D> Math::Factory::createVector3D()
{
    return std::make_unique<Math::Vector3D>();
}

std::unique_ptr<Math::Vector3D> Math::Factory::createVector3D(
    float x,
    float y,
    float z
)
{
    return std::make_unique<Math::Vector3D>(x, y, z);
}
