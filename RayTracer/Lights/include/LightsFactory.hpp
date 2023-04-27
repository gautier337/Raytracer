/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** LightsFactory
*/

#pragma once
#include "IFactory.hpp"
#include "Camera.hpp"
#include "DirectionalLight.hpp"
#include "Color.hpp"
#include <memory>

namespace RayTracer {
    namespace Lights {
        class LightsFactory : public IFactory {
            public:
                LightsFactory() = default;
                ~LightsFactory() override;
                std::unique_ptr<RayTracer::Lights::DirectionalLight> createDirectionalLight(
                    Math::Point3D origin,
                    Math::Vector3D direction,
                    double brightness,
                    Render::Color color
                );
        };
    }
}
