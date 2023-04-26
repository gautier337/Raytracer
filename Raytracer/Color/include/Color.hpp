/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Color
*/

#pragma once

namespace RayTracer {
    class Color {
        public:
            Color();
            ~Color();
            Color(double r, double g, double b, double a);
            Color(const Color &color);
            Color(Color &&color);
            Color &operator=(const Color &color);
            Color &operator=(Color &&color);
            Color &operator+=(const Color &color);
            Color &operator-=(const Color &color);
            Color &operator*=(const Color &color);
            Color &operator/=(const Color &color);
            double getR() const;
            double getG() const;
            double getB() const;
            double getA() const;
            void setR(double r);
            void setG(double g);
            void setB(double b);
            void setA(double a);
            void setRGBA(double r, double g, double b, double a);

        protected:
        private:
            double r;
            double g;
            double b;
            double a;
    };
}
