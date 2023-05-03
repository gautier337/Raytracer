/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Color
*/

#include "Color.hpp"
#include <memory>

RayTracer::Render::Color::Color() :
    r(0),
    g(0),
    b(0),
    a(1)
{}

RayTracer::Render::Color::~Color() {}

RayTracer::Render::Color::Color(
    double r,
    double g,
    double b,
    double a
) :
    r(r),
    g(g),
    b(b),
    a(a)
{}

RayTracer::Render::Color::Color(const Color &color) :
    r(color.r),
    g(color.g),
    b(color.b),
    a(color.a)
{}

RayTracer::Render::Color::Color(Color &&color) :
    r(color.r),
    g(color.g),
    b(color.b),
    a(color.a)
{}

RayTracer::Render::Color &RayTracer::Render::Color::operator=(const Color &color) {
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
    return *this;
}

RayTracer::Render::Color &RayTracer::Render::Color::operator=(Color &&color)
{
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
    return *this;
}

RayTracer::Render::Color &RayTracer::Render::Color::operator+=(const Color &color)
{
    r += color.r;
    g += color.g;
    b += color.b;
    a += color.a;
    return *this;
}

RayTracer::Render::Color &RayTracer::Render::Color::operator-=(const Color &color)
{
    r -= color.r;
    g -= color.g;
    b -= color.b;
    a -= color.a;
    return *this;
}

RayTracer::Render::Color &RayTracer::Render::Color::operator*=(const Color &color)
{
    r *= color.r;
    g *= color.g;
    b *= color.b;
    a *= color.a;
    return *this;
}

RayTracer::Render::Color &RayTracer::Render::Color::operator/=(const Color &color)
{
    r /= color.r;
    g /= color.g;
    b /= color.b;
    a /= color.a;
    return *this;
}

double RayTracer::Render::Color::getR() const
{
    return r;
}

double RayTracer::Render::Color::getG() const
{
    return g;
}

double RayTracer::Render::Color::getB() const
{
    return b;
}

double RayTracer::Render::Color::getA() const
{
    return a;
}

void RayTracer::Render::Color::setR(double r)
{
    this->r = r;
}

void RayTracer::Render::Color::setG(double g)
{
    this->g = g;
}

void RayTracer::Render::Color::setB(double b)
{
    this->b = b;
}

void RayTracer::Render::Color::setA(double a)
{
    this->a = a;
}

void RayTracer::Render::Color::setRGBA(
    double r,
    double g,
    double b,
    double a
)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

extern "C" std::unique_ptr<RayTracer::Render::Color> createColor(
    double r,
    double g,
    double b,
    double a
)
{
    return std::make_unique<RayTracer::Render::Color>(r, g, b, a);
}
