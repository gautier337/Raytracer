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
                Camera() = default;
                ~Camera();
                Camera(Math::Point3D origin, Math::Rectangle3D screen);
                Camera(const Camera &camera);
                Camera(Camera &&camera);
                Camera &operator=(const Camera &camera);
                Camera &operator=(Camera &&camera);
                Ray ray(double u, double v);
                void translate(Math::Vector3D translation);
                void rotate(Math::Vector3D rotation, double angle);
                Math::Point3D getOrigin() const;

            protected:
            private:
                Math::Point3D origin;
                Math::Rectangle3D screen;
        };
    };
};
