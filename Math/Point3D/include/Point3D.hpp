/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Point3d
*/

#pragma once
#include "Vector3D.hpp"

namespace Math {
    class Point3D {
        public:
            Point3D();
            ~Point3D();
            Point3D(double x, double y, double z);
            Point3D(const Point3D &point);
            Point3D(Point3D &&point);
            Point3D &operator=(const Point3D &point);
            Point3D &operator=(Point3D &&point);
            Point3D &operator+=(const Vector3D &vector);
            Point3D operator+(const Vector3D &vector);
            Point3D &operator-=(const Vector3D &vector);
            Point3D operator-(const Vector3D &vector);
            Point3D &operator+=(const Point3D &point);
            Point3D operator+(const Point3D &point);
            Point3D &operator-=(const Point3D &point);
            Point3D operator-(const Point3D &point);
            double getX() const;
            double getY() const;
            double getZ() const;
            void setX(double x);
            void setY(double y);
            void setZ(double z);
            double distance(const Point3D &point);

        protected:
        private:
            double x;
            double y;
            double z;
    };
};