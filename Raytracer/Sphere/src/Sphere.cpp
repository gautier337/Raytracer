/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"
#include <cmath>

RayTracer::Sphere::Sphere() : center(), radius(0)
{
}

RayTracer::Sphere::~Sphere()
{
}

RayTracer::Sphere::Sphere(Math::Point3D center, double radius) : center(center), radius(radius)
{
}

RayTracer::Sphere::Sphere(const Sphere &sphere) : center(sphere.center), radius(sphere.radius)
{
}

RayTracer::Sphere::Sphere(Sphere &&sphere) : center(sphere.center), radius(sphere.radius)
{
}

RayTracer::Sphere &RayTracer::Sphere::operator=(const Sphere &sphere)
{
    this->center = sphere.center;
    this->radius = sphere.radius;
    return *this;
}

RayTracer::Sphere &RayTracer::Sphere::operator=(Sphere &&sphere)
{
    this->center = sphere.center;
    this->radius = sphere.radius;
    return *this;
}

bool RayTracer::Sphere::hits(Ray ray)
{
    Math::Vector3D oc((ray.getOrigin() - this->center).getX(), (ray.getOrigin() - this->center).getY(), (ray.getOrigin() - this->center).getZ());

    double a = ray.getDirection().dot(ray.getDirection());
    double b = 2.0 * oc.dot(ray.getDirection());
    double c = oc.dot(oc) - this->radius * this->radius;
    double discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

void RayTracer::Sphere::translate(Math::Vector3D vector)
{
    this->center = this->center + vector;
}

void RayTracer::Sphere::rotateX(double angle)
{
    double radians = angle * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);
    double yPrime = cosA * this->center.getY() - sinA * this->center.getZ();
    double zPrime = sinA * this->center.getY() + cosA * this->center.getZ();
    this->center.setY(yPrime);
    this->center.setZ(zPrime);
}

void RayTracer::Sphere::rotateY(double angle)
{
    double radians = angle * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);
    double xPrime = cosA * this->center.getX() + sinA * this->center.getZ();
    double zPrime = -sinA * this->center.getX() + cosA * this->center.getZ();
    this->center.setX(xPrime);
    this->center.setZ(zPrime);
}

void RayTracer::Sphere::rotateZ(double angle)
{
    double radians = angle * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);
    double xPrime = cosA * this->center.getX() - sinA * this->center.getY();
    double yPrime = sinA * this->center.getX() + cosA * this->center.getY();
    this->center.setX(xPrime);
    this->center.setY(yPrime);
}
