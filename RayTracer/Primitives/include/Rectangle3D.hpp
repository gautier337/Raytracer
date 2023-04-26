/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Rectangle3D
*/

#pragma once
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"

namespace RayTracer {
    namespace Primitives {
        class Rectangle3D {
            public:
                Rectangle3D();
                ~Rectangle3D();
                Rectangle3D(
                    Math::Point3D origin,
                    Math::Vector3D bottom_side,
                    Math::Vector3D left_side,
                    Render::Color color
                );
                Rectangle3D(const Rectangle3D &rectangle);
                Rectangle3D(Rectangle3D &&rectangle);
                Rectangle3D &operator=(const Rectangle3D &rectangle);
                Rectangle3D &operator=(Rectangle3D &&rectangle);
                bool hits(View::Ray ray);
                Render::Color computeColor(View::Ray ray);
                Math::Point3D pointAt(double u, double v);
                void translate(Math::Vector3D translation);

            protected:
            private:
                Math::Point3D origin;
                Math::Vector3D bottom_side;
                Math::Vector3D left_side;
                Render::Color color;
        };
    };
};
