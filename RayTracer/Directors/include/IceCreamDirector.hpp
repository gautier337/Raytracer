/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** IceCreamDirector
*/

#pragma once
#include "IDirector.hpp"
#include "IceCreamBuilder.hpp"
#include "Cone.hpp"
#include "Sphere.hpp"

namespace RayTracer {
    class IObjects {
        public:
            virtual ~IObjects() = default;
            virtual std::vector<Primitives::Cone> getCone() const = 0;
            virtual std::vector<Primitives::Sphere> getScoops() const = 0;
    };
    namespace Directors {
        class IceCreamDirector : public IDirector {
            public:
                IceCreamDirector(Builders::IceCreamBuilder builder);
                ~IceCreamDirector();
                IceCreamDirector(const IceCreamDirector &iceCreamDirector);
                IceCreamDirector(IceCreamDirector &&iceCreamDirector);
                IceCreamDirector &operator=(const IceCreamDirector &iceCreamDirector);
                IceCreamDirector &operator=(IceCreamDirector &&iceCreamDirector);
                void make(
                    std::string const &type,
                    Math::Point3D position,
                    double scale
                ) override;
                CustomObject getObject() const override;

            private:
                void createOneScoopIceCream(
                    Math::Point3D position,
                    double scale
                );
                void createTwoScoopsIceCream(
                    Math::Point3D position,
                    double scale
                );
                void createThreeScoopsIceCream(
                    Math::Point3D position,
                    double scale
                );
                Builders::IceCreamBuilder builder;
        };
    };
}
