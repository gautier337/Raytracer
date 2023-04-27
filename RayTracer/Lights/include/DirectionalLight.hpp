/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** DirectionalLight
*/


#pragma once
#include "ILights.hpp"

namespace RayTracer {
    namespace Lights {
        class DirectionalLight : public ILights {
            public:
                DirectionalLight();
                ~DirectionalLight();
                DirectionalLight(
                    Math::Point3D origin,
                    Math::Vector3D direction,
                    double brightness,
                    Render::Color color
                );
                DirectionalLight(const DirectionalLight &light);
                DirectionalLight(DirectionalLight &&light);
                Math::Point3D getOrigin() const override;
                Math::Vector3D getDirection() const override;
                double getBrightness() const override;
                Render::Color getColor() const override;
                void setOrigin(Math::Point3D origin) override;
                void setDirection(Math::Vector3D direction) override;
                void setBrightness(double brightness) override;
                void setColor(Render::Color color) override;

            protected:
            private:
                Math::Point3D origin;
                Math::Vector3D direction;
                double brightness;
                Render::Color color;
        };
    };
};
