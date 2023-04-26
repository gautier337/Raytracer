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
#include "DirectionalLight.hpp"
#include <vector>

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
            Color computeColor(Ray ray, std::vector<DirectionalLight> lights);
            void translate(Math::Vector3D translation);
            void rotateX(double angle);
            void rotateY(double angle);
            void rotateZ(double angle);
            double getCenterX() const;
            double getCenterY() const;
            double getCenterZ() const;

        protected:
        private:
            Math::Point3D center;
            double radius;
            RayTracer::Color color;
    };
}
