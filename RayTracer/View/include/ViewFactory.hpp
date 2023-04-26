/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** ViewFactory
*/

#pragma once
#include "IFactory.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include <memory>

namespace RayTracer {
    namespace View {
        class ViewFactory : public IFactory {
            public:
                ViewFactory() = default;
                ~ViewFactory() override;
                std::unique_ptr<RayTracer::View::Camera> createCamera(
                    RayTracer::Math::Point3D position,
                    int width,
                    int height,
                    RayTracer::Math::Vector3D rotation,
                    double fov
                );
                std::unique_ptr<RayTracer::View::Ray> createRay(
                    RayTracer::Math::Point3D origin,
                    RayTracer::Math::Vector3D direction
                );
        };
    };
};
