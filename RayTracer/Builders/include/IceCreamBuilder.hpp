/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** IceCreamBuilder
*/

#pragma once
#include "IBuilder.hpp"
#include "Cone.hpp"
#include "Sphere.hpp"

namespace RayTracer {
    namespace Builders {
        class IceCreamBuilder : public IBuilder {
            public:
                IceCreamBuilder();
                ~IceCreamBuilder();
                IceCreamBuilder(const IceCreamBuilder &iceCreamBuilder);
                IceCreamBuilder(IceCreamBuilder &&iceCreamBuilder);
                IceCreamBuilder &operator=(const IceCreamBuilder &iceCreamBuilder);
                IceCreamBuilder &operator=(IceCreamBuilder &&iceCreamBuilder);
                void createCone(
                    Math::Point3D center,
                    Math::Vector3D axis,
                    double base_radius,
                    double apex_radius,
                    double height,
                    Render::Color color
                );
                void createScoop(
                    Math::Point3D center,
                    double radius,
                    Render::Color color
                );

            private:
                Primitives::Cone cone;
                std::vector<Primitives::Sphere> scoops;
        };
    };
}
