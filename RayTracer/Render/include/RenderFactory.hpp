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
                std::unique_ptr<RayTracer::Render::Color> createColor(
                    double r,
                    double g,
                    double b,
                    double a
                );
        };
    }
}
