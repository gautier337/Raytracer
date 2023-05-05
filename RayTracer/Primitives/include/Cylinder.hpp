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
#include "Color.hpp"
#include "IPrimitives.hpp"
#include "ILights.hpp"
#include <iostream>
#include <vector>
#include <memory>

namespace RayTracer {
    namespace Primitives {
        class Cylinder : public IPrimitives {
            public:
                Cylinder();
                ~Cylinder();
                Cylinder(Math::Point3D center,
                    Math::Vector3D axis,
                    double radius,
                    double height,
                    Render::Color color
                );
                Cylinder(const Cylinder &cylinder);
                Cylinder(Cylinder &&cylinder);
                Cylinder &operator=(const Cylinder &cylinder);
                Cylinder &operator=(Cylinder &&cylinder);
                double getIntersectionPoint(View::Ray ray) override;
                bool hits(View::Ray ray);
                Render::Color computeColor(
                        View::Ray ray,
                        std::vector<std::unique_ptr<ILights>> &lights
                ) override;
                void translate(Math::Vector3D translation) override;
                void rotate(Math::Vector3D axis, double angle) override;
                void scale(double factor) override;

            protected:
            private:
                Math::Point3D center;
                Math::Vector3D axis;
                double radius;
                double height;
                double closestT;
                Render::Color color;
        };
    }
}