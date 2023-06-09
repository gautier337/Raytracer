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
#include "IPrimitive.hpp"
#include "ILights.hpp"
#include <iostream>
#include <vector>
#include <memory>

namespace RayTracer {
    namespace Primitives {
        class Cone : public IPrimitive {
            public:
                Cone();
                ~Cone();
                Cone(
                    Math::Point3D center,
                    Math::Vector3D axis,
                    double base_radius,
                    double apex_radius,
                    double height,
                    Render::Color color
                );
                Cone(const Cone &cone);
                Cone(Cone &&cone);
                Cone &operator=(const Cone &cone);
                Cone &operator=(Cone &&cone);
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
                void setColor(Render::Color color) override;
                std::unique_ptr<IPrimitive> clone() const override;

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
