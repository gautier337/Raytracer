/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"
#include <cmath>

RayTracer::Primitives::Sphere::Sphere() :
    center(),
    radius(0),
    color(0, 0, 0, 1),
    closestT(__FLT_MAX__)
{
}

RayTracer::Primitives::Sphere::~Sphere()
{
}

RayTracer::Primitives::Sphere::Sphere(
    Math::Point3D center,
    double radius,
    RayTracer::Render::Color color
) :
    center(center),
    radius(radius),
    color(color),
    closestT(__FLT_MAX__)
{
}

RayTracer::Primitives::Sphere::Sphere(const Sphere &sphere) :
    center(sphere.center),
    radius(sphere.radius),
    color(sphere.color),
    closestT(sphere.closestT)
{
}

RayTracer::Primitives::Sphere::Sphere(Sphere &&sphere) :
    center(sphere.center),
    radius(sphere.radius),
    color(sphere.color),
    closestT(sphere.closestT)
{
}

RayTracer::Primitives::Sphere &RayTracer::Primitives::Sphere::operator=(
    const Sphere &sphere
)
{
    this->center = sphere.center;
    this->radius = sphere.radius;
    this->color = sphere.color;
    this->closestT = sphere.closestT;
    return *this;
}

RayTracer::Primitives::Sphere &RayTracer::Primitives::Sphere::operator=(
    Sphere &&sphere
)
{
    this->center = sphere.center;
    this->radius = sphere.radius;
    this->color = sphere.color;
    this->closestT = sphere.closestT;
    return *this;
}

double RayTracer::Primitives::Sphere::getIntersectionPoint(View::Ray ray)
{
    RayTracer::Math::Vector3D oc(
        (ray.getOrigin() - this->center).getX(),
        (ray.getOrigin() - this->center).getY(),
        (ray.getOrigin() - this->center).getZ()
    );

    double a = ray.getDirection().dot(ray.getDirection());
    double b = 2.0 * oc.dot(ray.getDirection());
    double c = oc.dot(oc) - this->radius * this->radius;
    double discriminant = b * b - 4 * a * c;
    double closestT = (-b - sqrt(discriminant)) / (2.0 * a);
    if (closestT < 0)
        closestT = (-b + sqrt(discriminant)) / (2.0 * a);
    this->closestT = closestT;
    return closestT;
}

bool RayTracer::Primitives::Sphere::hits(View::Ray ray)
{
    Math::Vector3D oc(
        (ray.getOrigin() - this->center).getX(),
        (ray.getOrigin() - this->center).getY(),
        (ray.getOrigin() - this->center).getZ()
    );

    double a = ray.getDirection().dot(ray.getDirection());
    double b = 2.0 * oc.dot(ray.getDirection());
    double c = oc.dot(oc) - this->radius * this->radius;
    double discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

RayTracer::Render::Color RayTracer::Primitives::Sphere::computeColor(
    RayTracer::View::Ray ray,
    std::vector<std::unique_ptr<ILights>> &lights
)
{
    RayTracer::Math::Point3D hitPoint = ray.getOrigin() + ray.getDirection() * this->closestT;
    RayTracer::Math::Vector3D non_normal(
        (this->center - hitPoint).getX() * 2,
        (this->center - hitPoint).getY() * 2,
        (this->center - hitPoint).getZ() * 2
    );
    RayTracer::Math::Vector3D normal = non_normal.normalize();

    RayTracer::Render::Color newColor(0, 0, 0, this->color.getA());

    for (const auto &light : lights) {
        double dot = std::max(0.0, normal.dot(light->getDirection()));
        double brightness = light->getBrightness();

        RayTracer::Render::Color lightColor(
            this->color.getR() * dot * brightness,
            this->color.getG() * dot * brightness,
            this->color.getB() * dot * brightness,
            0
        );

        newColor += lightColor;
    }

    return newColor;
}

void RayTracer::Primitives::Sphere::translate(Math::Vector3D translation)
{
    this->center = this->center + translation;
}

void RayTracer::Primitives::Sphere::rotate(Math::Vector3D axis, double angle)
{
    double radians = angle * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);
    double xPrime = (cosA + (1 - cosA) * axis.getX() * axis.getX()) * this->center.getX() + ((1 - cosA) * axis.getX() * axis.getY() - sinA * axis.getZ()) * this->center.getY() + ((1 - cosA) * axis.getX() * axis.getZ() + sinA * axis.getY()) * this->center.getZ();
    double yPrime = ((1 - cosA) * axis.getX() * axis.getY() + sinA * axis.getZ()) * this->center.getX() + (cosA + (1 - cosA) * axis.getY() * axis.getY()) * this->center.getY() + ((1 - cosA) * axis.getY() * axis.getZ() - sinA * axis.getX()) * this->center.getZ();
    double zPrime = ((1 - cosA) * axis.getX() * axis.getZ() - sinA * axis.getY()) * this->center.getX() + ((1 - cosA) * axis.getY() * axis.getZ() + sinA * axis.getX()) * this->center.getY() + (cosA + (1 - cosA) * axis.getZ() * axis.getZ()) * this->center.getZ();
    this->center.setX(xPrime);
    this->center.setY(yPrime);
    this->center.setZ(zPrime);
}

void RayTracer::Primitives::Sphere::scale(double factor)
{
    this->radius *= factor;
}