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
    RayTracer::Camera cam;
    RayTracer::Sphere s(Math::Point3D(5, 5, -10), 3);

    std::cout << "P3" << std::endl;
    std::cout << "100 100" << std::endl;
    std::cout << "255" << std::endl;
    for (double y = 0; y < 1; y += 0.010) {
        for (double x = 0; x < 1; x += 0.010) {
            double u = x;
            double v = y;
            RayTracer::Ray r = cam.ray(u, v);
            if (s.hits(r)) {
                std::cout << "255 0 0" << std::endl;
            } else {
                std::cout << "0 0 255" << std::endl;
            }
        }
    }
    return SUCCESS;
}
