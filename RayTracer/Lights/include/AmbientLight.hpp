/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** AmbientLight
*/


#pragma once
#include "ILights.hpp"

namespace RayTracer {
    namespace Lights {
        class AmbientLight : public ILights {
            public:
                AmbientLight();
                ~AmbientLight();
                AmbientLight(double brightness, Render::Color color);
                AmbientLight(const AmbientLight &light);
                AmbientLight(AmbientLight &&light);
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
                double brightness;
                Render::Color color;
        };
    };
};
