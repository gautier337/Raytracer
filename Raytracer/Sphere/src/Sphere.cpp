/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"
#include <cmath>

RayTracer::Sphere::Sphere() : center(), radius(0), color(0, 0, 0, 1)
{
}

RayTracer::Sphere::~Sphere()
{
}

RayTracer::Sphere::Sphere(Math::Point3D center, double radius, RayTracer::Color color) : center(center), radius(radius), color(color)
{
}

RayTracer::Sphere::Sphere(const Sphere &sphere) : center(sphere.center), radius(sphere.radius), color(sphere.color)
{
}

RayTracer::Sphere::Sphere(Sphere &&sphere) : center(sphere.center), radius(sphere.radius), color(sphere.color)
{
}

RayTracer::Sphere &RayTracer::Sphere::operator=(const Sphere &sphere)
{
    this->center = sphere.center;
    this->radius = sphere.radius;
    this->color = sphere.color;
    return *this;
}

RayTracer::Sphere &RayTracer::Sphere::operator=(Sphere &&sphere)
{
    this->center = sphere.center;
    this->radius = sphere.radius;
    this->color = sphere.color;
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

RayTracer::Color RayTracer::Sphere::computeColor(Ray ray)
{
    RayTracer::Color newColor(0, 0, 0, 1);
    Math::Point3D origin = ray.getOrigin();

    if (!this->hits(ray))
        return newColor;
    Math::Vector3D oc(
        (origin - this->center).getX(),
        (origin - this->center).getY(),
        (origin - this->center).getZ()
    );
    double a = ray.getDirection().dot(ray.getDirection());
    double b = 2.0 * oc.dot(ray.getDirection());
    double c = oc.dot(oc) - this->radius * this->radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return color;
    double t = (-b - sqrt(discriminant)) / (2.0 * a);
    Math::Vector3D hitPoint(
        origin.getX() + t * ray.getDirection().getX(),
        origin.getY() + t * ray.getDirection().getY(),
        origin.getZ() + t * ray.getDirection().getZ()
    );
    newColor.setRGBA(
        this->color.getR() * (hitPoint.getX() * (this->radius / 2) + (this->radius / 2)),
        this->color.getG() * (hitPoint.getY() * (this->radius / 2) + (this->radius / 2)),
        this->color.getB() * (hitPoint.getZ() * (this->radius / 2) + (this->radius / 2)),
        this->color.getA()
    );
    return newColor;
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

double RayTracer::Sphere::getCenterX() const
{
    return this->center.getX();
}

double RayTracer::Sphere::getCenterY() const
{
    return this->center.getY();
}

double RayTracer::Sphere::getCenterZ() const
{
    return this->center.getZ();
}
