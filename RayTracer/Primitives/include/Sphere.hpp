/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Sphere
*/

#pragma once
#include "IPrimitive.hpp"
#include "Point3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "ILights.hpp"
#include <vector>
#include <string>

namespace RayTracer {
    namespace Primitives {
        class Sphere : public IPrimitive {
            public:
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
                    std::vector<std::unique_ptr<ILights>> &lights,
                    std::vector<std::unique_ptr<IPrimitive>> &primitives
                ) override;
                void translate(Math::Vector3D translation) override;
                void rotate(Math::Vector3D axis, double angle) override;
                void scale(double factor) override;
                std::string getType() const override;
                Render::Color getColor() const override;
                void setColor(Render::Color color);
                std::unique_ptr<IPrimitive> clone() const override;

            protected:
            private:
                Math::Point3D center;
                double radius;
                Render::Color color;
                double closestT;
        };
    };
};
