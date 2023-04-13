/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** IVector3D
*/

#pragma once
#include <cmath>
#include <vector>

namespace Math {
    class IVector3D {
        public:
            virtual ~IVector3D() = default;
            virtual IVector3D &operator=(const IVector3D &vector) = 0;
            virtual IVector3D &operator=(IVector3D &&vector) = 0;
            virtual IVector3D &operator+=(const IVector3D &vector) = 0;
            virtual IVector3D &operator-=(const IVector3D &vector) = 0;
            virtual IVector3D &operator*=(const IVector3D &vector) = 0;
            virtual IVector3D &operator/=(const IVector3D &vector) = 0;
            virtual IVector3D &operator+(const IVector3D &vector) = 0;
            virtual IVector3D &operator-(const IVector3D &vector) = 0;
            virtual IVector3D &operator*(const IVector3D &vector) = 0;
            virtual IVector3D &operator/(const IVector3D &vector) = 0;
            virtual IVector3D &operator+=(double value) = 0;
            virtual IVector3D &operator-=(double value) = 0;
            virtual IVector3D &operator*=(double value) = 0;
            virtual IVector3D &operator/=(double value) = 0;
            virtual IVector3D &operator+(double value) = 0;
            virtual IVector3D &operator-(double value) = 0;
            virtual IVector3D &operator*(double value) = 0;
            virtual IVector3D &operator/(double value) = 0;
            virtual double length() = 0;
            virtual double dot(const IVector3D &vector) = 0;
            virtual double getX() const = 0;
            virtual double getY() const = 0;
            virtual double getZ() const = 0;
    };
};
