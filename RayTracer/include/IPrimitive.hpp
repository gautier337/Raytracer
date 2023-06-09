/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** IPrimitive
*/

#pragma once
#include <string>
#include <vector>
#include "Ray.hpp"
#include "Color.hpp"
#include "DirectionalLight.hpp"
#include <memory>

namespace RayTracer {
    class IPrimitive {
        public:
            virtual ~IPrimitive() = default;
            virtual double getIntersectionPoint(View::Ray ray) = 0;
            virtual bool hits(View::Ray ray) = 0;
            virtual Render::Color computeColor(
                View::Ray ray,
                std::vector<std::unique_ptr<ILights>> &lights,
                std::vector<std::unique_ptr<IPrimitive>> &primitives
            ) = 0;
            virtual void translate(Math::Vector3D translation) = 0;
            virtual void rotate(Math::Vector3D axis, double angle) = 0;
            virtual void scale(double factor) = 0;
            virtual std::string getType() const = 0;
            virtual Render::Color getColor() const = 0;
            virtual void setColor(Render::Color color) = 0;
            virtual std::unique_ptr<IPrimitive> clone() const = 0;
    };
}
