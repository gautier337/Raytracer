/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Point3d
*/

#pragma once

namespace Maths {
    class Point3D {
        public:
            Point3D();
            ~Point3D();
            Point3D(double x, double y, double z);
            Point3D(const Point3D &point);
            Point3D(Point3D &&point) noexcept;
            Point3D &operator=(const Point3D &point);
            Point3D &operator=(Point3D &&point) noexcept;

        protected:
        private:
        double x;
        double y;
        double z;
    };
};