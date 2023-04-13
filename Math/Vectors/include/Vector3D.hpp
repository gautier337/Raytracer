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
            ~Vector3D() override;
            Vector3D(double x, double y, double z);
            Vector3D(const Vector3D &vector);
            Vector3D(Vector3D &&vector);
            IVector3D &operator=(const IVector3D &vector) override;
            IVector3D &operator=(IVector3D &&vector);
            IVector3D &operator+=(const IVector3D &vector);
            IVector3D &operator-=(const IVector3D &vector);
            IVector3D &operator*=(const IVector3D &vector);
            IVector3D &operator/=(const IVector3D &vector);
            IVector3D &operator+(const IVector3D &vector);
            IVector3D &operator-(const IVector3D &vector);
            IVector3D &operator*(const IVector3D &vector);
            IVector3D &operator/(const IVector3D &vector);
            IVector3D &operator+=(double value);
            IVector3D &operator-=(double value);
            IVector3D &operator*=(double value);
            IVector3D &operator/=(double value);
            IVector3D &operator+(double value);
            IVector3D &operator-(double value);
            IVector3D &operator*(double value);
            IVector3D &operator/(double value);
            double length() override;
            double dot(const IVector3D &vector);
            double getX() const;
            double getY() const;
            double getZ() const;

        protected:
        private:
            double x;
            double y;
            double z;
    };
};
