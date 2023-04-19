/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Rectangle
*/

#pragma once
#include "Point3D.hpp"

namespace RayTracer {
    class Rectangle3D {
        public:
            Rectangle3D();
            ~Rectangle3D();
            Rectangle3D(Math::Point3D origin, Math::Vector3D bottom_side, Math::Vector3D left_side);
            Rectangle3D(const Rectangle3D &rectangle);
            Rectangle3D(Rectangle3D &&rectangle);
            Rectangle3D &operator=(const Rectangle3D &rectangle);
            Rectangle3D &operator=(Rectangle3D &&rectangle);
            Math::Point3D pointAt(double u, double v);

        protected:
        private:
            Math::Point3D origin;
            Math::Vector3D bottom_side;
            Math::Vector3D left_side;
    };
}