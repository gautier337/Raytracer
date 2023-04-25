/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Sphere
*/

#pragma once
#include "Point3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"

namespace RayTracer {
    class Sphere {
        public:
            Sphere();
            ~Sphere();
            Sphere(Math::Point3D center, double radius, RayTracer::Color color);
            Sphere(const Sphere &sphere);
            Sphere(Sphere &&sphere);
            Sphere &operator=(const Sphere &sphere);
            Sphere &operator=(Sphere &&sphere);
            bool hits(Ray ray);
            Color computeColor(Ray ray);
            void translate(Math::Vector3D translation);
            void rotateX(double angle);
            void rotateY(double angle);
            void rotateZ(double angle);

        protected:
        private:
            Math::Point3D center;
            double radius;
            RayTracer::Color color;
    };
}
