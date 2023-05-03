/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Sphere
*/

#pragma once
#include "IPrimitives.hpp"
#include "Point3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "ILights.hpp"
#include <vector>

namespace RayTracer {
    namespace Primitives {
        class Sphere : public IPrimitives {
            public:
                Sphere();
                ~Sphere();
                Sphere(
                    Math::Point3D center,
                    double radius,
                    Render::Color color
                );
                Sphere(const Sphere &sphere);
                Sphere(Sphere &&sphere);
                Sphere &operator=(const Sphere &sphere);
                Sphere &operator=(Sphere &&sphere);
                double getIntersectionPoint(View::Ray ray) override;
                bool hits(View::Ray ray) override;
                Render::Color computeColor(
                    View::Ray ray,
                    std::vector<std::unique_ptr<ILights>> &lights
                ) override;
                void translate(Math::Vector3D translation) override;
                void rotate(Math::Vector3D axis, double angle) override;

            protected:
            private:
                Math::Point3D center;
                double radius;
                Render::Color color;
                double closestT;
        };
    };
};
