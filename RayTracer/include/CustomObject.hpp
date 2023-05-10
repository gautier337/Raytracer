/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** CustomObject
*/

#pragma once
#include <vector>
#include "IPrimitive.hpp"

namespace RayTracer {
    class CustomObject {
        public:
            CustomObject();
            ~CustomObject();
            CustomObject(const CustomObject &customObject);
            CustomObject(CustomObject &&customObject);
            CustomObject &operator=(const CustomObject &customObject);
            CustomObject &operator=(CustomObject &&customObject);
            void addPrimitive(std::unique_ptr<IPrimitive> primitive);
            double getIntersectionPoint(View::Ray ray);
            bool hits(View::Ray ray);
            Render::Color computeColor(
                View::Ray ray,
                std::vector<std::unique_ptr<ILights>> &lights,
                std::vector<std::unique_ptr<IPrimitive>> &primitives
            );

        protected:
        private:
            std::vector<std::unique_ptr<IPrimitive>> primitives;
            double closestT;
    };
}
