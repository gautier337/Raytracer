/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Rectangle
*/

#pragma once
#include "Point3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"

namespace RayTracer {
    class Rectangle3D {
        public:
            Rectangle3D();
            ~Rectangle3D();
            Rectangle3D(
                Math::Point3D origin,
                Math::Vector3D bottom_side,
                Math::Vector3D left_side,
                Color color
            );
            Rectangle3D(const Rectangle3D &rectangle);
            Rectangle3D(Rectangle3D &&rectangle);
            Rectangle3D &operator=(const Rectangle3D &rectangle);
            Rectangle3D &operator=(Rectangle3D &&rectangle);
            bool hits(Ray ray);
            Color computeColor(Ray ray);
            Math::Point3D pointAt(double u, double v);
            void translate(Math::Vector3D translation);

        protected:
        private:
            Math::Point3D origin;
            Math::Vector3D bottom_side;
            Math::Vector3D left_side;
            RayTracer::Color color;
    };
}
