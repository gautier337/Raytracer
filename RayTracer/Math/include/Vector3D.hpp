/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Vector3D
*/

#pragma once

namespace RayTracer {
    namespace Math {
        class Vector3D {
            public:
                Vector3D();
                ~Vector3D();
                Vector3D(double x, double y, double z);
                Vector3D(const Vector3D &vector);
                Vector3D(Vector3D &&vector);
                Vector3D &operator=(const Vector3D &vector);
                Vector3D &operator=(Vector3D &&vector);
                Vector3D &operator+=(const Vector3D &vector);
                Vector3D &operator-=(const Vector3D &vector);
                Vector3D &operator*=(const Vector3D &vector);
                Vector3D &operator/=(const Vector3D &vector);
                Vector3D &operator+(const Vector3D &vector);
                Vector3D &operator-(const Vector3D &vector);
                Vector3D &operator*(const Vector3D &vector);
                Vector3D &operator/(const Vector3D &vector);
                bool &operator==(const Vector3D &vector);
                bool &operator!=(const Vector3D &vector);
                Vector3D &operator+=(double value);
                Vector3D &operator-=(double value);
                Vector3D &operator*=(double value);
                Vector3D &operator/=(double value);
                Vector3D operator+(double value);
                Vector3D operator-(double value);
                Vector3D operator*(double value);
                Vector3D operator/(double value);
                double length();
                double dot(const Vector3D &vector);
                double getX() const;
                double getY() const;
                double getZ() const;
                Vector3D normalize();
                Vector3D cross(const Vector3D &v);
                void rotate(Vector3D axis, double angle);

            protected:
            private:
                double x;
                double y;
                double z;
        };
    };
};
