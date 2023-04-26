/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Ray
*/


#pragma once
#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
    namespace View {
        class Ray {
            public:
                Ray();
                ~Ray();
                Ray(
                    Math::Point3D origin,
                    Math::Vector3D direction
                );
                Ray(const Ray &ray);
                Ray(Ray &&ray);
                Ray &operator=(const Ray &ray);
                Ray &operator=(Ray &&ray);
                Math::Point3D getOrigin() const;
                Math::Vector3D getDirection() const;

            protected:
            private:
                Math::Point3D origin;
                Math::Vector3D direction;
        };
    };
};
