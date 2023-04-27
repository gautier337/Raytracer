/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** ILights
*/

#pragma once
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Color.hpp"

namespace RayTracer {
    class ILights {
        public:
            virtual ~ILights() = default;
            virtual Math::Point3D getOrigin() const = 0;
            virtual Math::Vector3D getDirection() const = 0;
            virtual double getBrightness() const = 0;
            virtual Render::Color getColor() const = 0;
            virtual void setOrigin(Math::Point3D origin) = 0;
            virtual void setDirection(Math::Vector3D direction) = 0;
            virtual void setBrightness(double brightness) = 0;
            virtual void setColor(Render::Color color) = 0;
    };
}
