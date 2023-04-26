/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** DirectionalLight
*/


#pragma once
#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
    namespace Lights {
        class DirectionalLight {
            public:
                DirectionalLight();
                ~DirectionalLight();
                DirectionalLight(
                    Math::Point3D origin,
                    Math::Vector3D direction,
                    double brightness
                );
                DirectionalLight(const DirectionalLight &light);
                DirectionalLight(DirectionalLight &&light);
                DirectionalLight &operator=(const DirectionalLight &light);
                DirectionalLight &operator=(DirectionalLight &&light);
                Math::Point3D getOrigin() const;
                Math::Vector3D getDirection() const;
                double getBrightness() const;

            protected:
            private:
                Math::Point3D origin;
                Math::Vector3D direction;
                double brightness;
        };
    };
};
