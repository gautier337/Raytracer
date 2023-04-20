/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Camera
*/

#pragma once
#include "Rectangle3D.hpp"
#include "Ray.hpp"

namespace RayTracer {
    class Camera {
        public:
            Camera();
            ~Camera();
            Camera(Math::Point3D origin, Rectangle3D screen);
            Camera(const Camera &camera);
            Camera(Camera &&camera);
            Camera &operator=(const Camera &camera);
            Camera &operator=(Camera &&camera);
            Ray ray(double u, double v);
            void translate(Math::Vector3D translation);
            void rotate(double x, double y);

        protected:
        private:
            Math::Point3D origin;
            Rectangle3D screen;
    };
}