/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Raytracer
*/

#include "Raytracer.hpp"
#include "IFactory.hpp"
#include "Vector3D.hpp"
#include "Factory.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include <memory>

int raytracer(std::string const &sceneFile)
{
    /*Math::Factory factory;
    std::unique_ptr<Math::IVector3D> vector = factory.createVector3D(1, 2, 3);
    std::unique_ptr<Math::IVector3D> vector2 = factory.createVector3D(4, 5, 6);
    std::cout << vector->length() << std::endl;
    *vector += *vector2;
    std::cout << vector->length() << std::endl;*/

    RayTracer::Camera cam;
    RayTracer::Sphere s(Math::Point3D(0, 0, -1), 0.5);
    for (float x = 0; x < 1; x += 0.1) {
        for (float y = 0; y < 1; y += 0.1) {
            double u = x;
            double v = y;
            RayTracer::Ray r = cam.ray (u, v);
            if (s.hits(r)) {
                std::cout << "X";
            } else {
                std::cout << " ";
            }
        }
    }
    return SUCCESS;
}
