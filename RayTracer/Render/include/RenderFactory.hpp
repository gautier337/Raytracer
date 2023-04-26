/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** RenderFactory
*/

#pragma once
#include "IFactory.hpp"
#include "Camera.hpp"
#include <memory>

namespace RayTracer {
    namespace Render {
        class RenderFactory : public IFactory {
            public:
                RenderFactory() = default;
                ~RenderFactory() override;
                std::unique_ptr<RayTracer::View::Camera> createView(
                    Math::Point3D origin,
                    Primitives::Rectangle3D screen
                );
        };
    }
}
