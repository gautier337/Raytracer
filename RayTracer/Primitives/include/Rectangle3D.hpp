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
#include "ILights.hpp"
#include <string>

namespace RayTracer {
    namespace Primitives {
        class Rectangle3D {
            public:
                ~Rectangle3D();
                Rectangle3D(
                    Math::Point3D origin,
                    Math::Vector3D bottom_side,
                    Math::Vector3D left_side
                );
                Rectangle3D(const Rectangle3D &rectangle);
                Rectangle3D(Rectangle3D &&rectangle);
                Rectangle3D &operator=(const Rectangle3D &rectangle);
                Rectangle3D &operator=(Rectangle3D &&rectangle);
                Math::Point3D pointAt(double u, double v);
                void translate(Math::Vector3D translation);
                void rotate(Math::Vector3D rotation, double angle);
                void scale(double factor);

            protected:
            private:
                Math::Point3D origin;
                Math::Vector3D bottom_side;
                Math::Vector3D left_side;
        };
    };
};
