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
    return SUCCESS;
}
