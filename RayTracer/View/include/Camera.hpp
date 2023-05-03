/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Camera
*/

#pragma once
#include "Rectangle3D.hpp"
#include "Point3D.hpp"
#include "Ray.hpp"

namespace RayTracer {
    namespace View {
        class Camera {
            public:
                Camera();
                ~Camera();
                Camera(Math::Point3D origin, Primitives::Rectangle3D screen, std::string direction);
                Camera(const Camera &camera);
                Camera(Camera &&camera);
                Camera &operator=(const Camera &camera);
                Camera &operator=(Camera &&camera);
                Ray ray(double u, double v);
                void translate(Math::Vector3D translation);
                void rotate(Math::Vector3D rotation, double angle);

            protected:
            private:
                Math::Point3D origin;
                Primitives::Rectangle3D screen;
                std::string direction;
        };
    };
};
