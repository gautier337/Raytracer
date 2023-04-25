/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Cylinder
*/

#pragma once
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"
#include <iostream>

namespace RayTracer {
    class Cylinder {
        public:
            Cylinder();
            ~Cylinder();
            Cylinder(Math::Point3D center, Math::Vector3D axis, double radius, double height);
            Cylinder(const Cylinder &cylinder);
            Cylinder(Cylinder &&cylinder);
            Cylinder &operator=(const Cylinder &cylinder);
            Cylinder &operator=(Cylinder &&cylinder);
            bool hits(Ray ray);

        protected:
        private:
            Math::Point3D center;
            Math::Vector3D axis;
            double radius;
            double height;
    };
}
