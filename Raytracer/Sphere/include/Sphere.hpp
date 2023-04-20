/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Sphere
*/


#pragma once
#include "Point3D.hpp"
#include "Ray.hpp"

namespace RayTracer {
    class Sphere {
        public:
            Sphere();
            ~Sphere();
            Sphere(Math::Point3D center, double radius);
            Sphere(const Sphere &sphere);
            Sphere(Sphere &&sphere);
            Sphere &operator=(const Sphere &sphere);
            Sphere &operator=(Sphere &&sphere);
            bool hits(Ray ray);

        protected:
        private:
            Math::Point3D center;
            double radius;
    };
}