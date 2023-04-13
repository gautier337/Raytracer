/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Raytracer
*/

#include "Raytracer.hpp"
#include "IFactory.hpp"
#include "IVector3D.hpp"
#include "Factory.hpp"
#include <memory>

int raytracer(std::string const &sceneFile)
{
    Math::Factory factory;
    std::unique_ptr<Math::IVector3D> vector = factory.createVector3D(1, 2, 3);
    std::unique_ptr<Math::IVector3D> vector2 = factory.createVector3D(4, 5, 6);
    std::cout << vector->length() << std::endl;
    *vector += *vector2;
    std::cout << vector->length() << std::endl;
    return SUCCESS;
}
