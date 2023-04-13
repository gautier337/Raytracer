/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Vector3D
*/

#pragma once
#include "IVector3D.hpp"

namespace Math {
    class Vector3D : public IVector3D {
        public:
            Vector3D();
            ~Vector3D();
            Vector3D(double x, double y, double z);
            double length();
            Vector3D(const Vector3D &vector);
            Vector3D(Vector3D &&vector);
            Vector3D &operator=(const Vector3D &vector);
            Vector3D &operator=(Vector3D &&vector);

        protected:
        private:
            double x;
            double y;
            double z;
    };
};
