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
#include "Color.hpp"
#include "IPrimitives.hpp"
#include "ILights.hpp"
#include <iostream>
#include <vector>
#include <memory>

namespace RayTracer {
    namespace Primitives {
        class Cone : public IPrimitives {
            public:
                Cone();
                ~Cone();
                Cone(Math::Point3D center, Math::Vector3D axis, double base_radius, double apex_radius, double height);
                Cone(const Cone &cone);
                Cone(Cone &&cone);
                Cone &operator=(const Cone &cone);
                Cone &operator=(Cone &&cone);
                bool hits(View::Ray ray);
                Render::Color computeColor(
                        View::Ray ray,
                        std::vector<std::unique_ptr<ILights>> &lights
                ) override;
                double getIntersectionPoint(View::Ray ray);

            protected:
            private:
                Math::Point3D center;
                Math::Vector3D axis;
                double base_radius;
                double apex_radius;
                double height;
                double closestT;
                Render::Color color;
        };
    };
}
