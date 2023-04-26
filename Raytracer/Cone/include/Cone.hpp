/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Cone3D
*/

#pragma once
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"
#include <iostream>

namespace RayTracer {
    class Cone {
        public:
            Cone();
            ~Cone();
            Cone(Math::Point3D center, Math::Vector3D axis, double base_radius, double apex_radius, double height);
            Cone(const Cone &cone);
            Cone(Cone &&cone);
            Cone &operator=(const Cone &cone);
            Cone &operator=(Cone &&cone);
            bool hits(Ray ray);

        protected:
        private:
            Math::Point3D center;
            Math::Vector3D axis;
            double base_radius;
            double apex_radius;
            double height;
    };
}
