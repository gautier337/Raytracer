/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Plane
*/

#pragma once
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "IPrimitives.hpp"
#include "ILights.hpp"

namespace RayTracer {
    namespace Primitives {
        class Plane : public IPrimitives {
            public:
                ~Plane();
                Plane(
                    std::string axis,
                    double position,
                    Render::Color color
                );
                Plane(const Plane &rectangle);
                Plane(Plane &&rectangle);
                Plane &operator=(const Plane &rectangle);
                Plane &operator=(Plane &&rectangle);
                double getIntersectionPoint(View::Ray ray) override;
                bool hits(View::Ray ray) override;
                Render::Color computeColor(
                    View::Ray ray,
                    std::vector<std::unique_ptr<ILights>> &lights
                ) override;
                Math::Point3D pointAt(double u, double v);
                void translate(Math::Vector3D translation) override;
                void rotate(Math::Vector3D rotation, double angle) override;
                void scale(double factor) override;

            protected:
            private:
                std::string axis;
                double position;
                Render::Color color;
                Math::Vector3D bottom_side;
                Math::Vector3D left_side;
                Math::Point3D origin;
        };
    };
};
