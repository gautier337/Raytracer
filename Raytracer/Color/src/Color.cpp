/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Color
*/

#include "Color.hpp"

RayTracer::Color::Color() :
    r(0),
    g(0),
    b(0),
    a(1)
{}

RayTracer::Color::~Color() {}

RayTracer::Color::Color(double r, double g, double b, double a) :
    r(r),
    g(g),
    b(b),
    a(a)
{}

RayTracer::Color::Color(const Color &color) :
    r(color.r),
    g(color.g),
    b(color.b),
    a(color.a)
{}

RayTracer::Color::Color(Color &&color) :
    r(color.r),
    g(color.g),
    b(color.b),
    a(color.a)
{}

RayTracer::Color &RayTracer::Color::operator=(const Color &color) {
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
    return *this;
}

RayTracer::Color &RayTracer::Color::operator=(Color &&color) {
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
    return *this;
}

double RayTracer::Color::getR() const
{
    return r;
}

double RayTracer::Color::getG() const
{
    return g;
}

double RayTracer::Color::getB() const
{
    return b;
}

double RayTracer::Color::getA() const
{
    return a;
}

void RayTracer::Color::setR(double r)
{
    this->r = r;
}

void RayTracer::Color::setG(double g)
{
    this->g = g;
}

void RayTracer::Color::setB(double b)
{
    this->b = b;
}

void RayTracer::Color::setA(double a)
{
    this->a = a;
}

void RayTracer::Color::setRGBA(double r, double g, double b, double a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}
