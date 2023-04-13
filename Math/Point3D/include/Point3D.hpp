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

        protected:
        private:
        double x;
        double y;
        double z;
    };
};