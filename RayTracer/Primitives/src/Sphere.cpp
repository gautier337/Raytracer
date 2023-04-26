/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"
#include <cmath>

RayTracer::Primitives::Sphere::Sphere() : center(), radius(0), color(0, 0, 0, 1)
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
    color(color)
{
}

RayTracer::Primitives::Sphere::Sphere(const Sphere &sphere) :
    center(sphere.center),
    radius(sphere.radius),
    color(sphere.color)
{
}

RayTracer::Primitives::Sphere::Sphere(Sphere &&sphere) :
    center(sphere.center),
    radius(sphere.radius),
    color(sphere.color)
{
}

RayTracer::Primitives::Sphere &RayTracer::Primitives::Sphere::operator=(
    const Sphere &sphere
)
{
    this->center = sphere.center;
    this->radius = sphere.radius;
    this->color = sphere.color;
    return *this;
}

RayTracer::Primitives::Sphere &RayTracer::Primitives::Sphere::operator=(
    Sphere &&sphere
)
{
    this->center = sphere.center;
    this->radius = sphere.radius;
    this->color = sphere.color;
    return *this;
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
    std::vector<RayTracer::Lights::DirectionalLight> lights
)
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
    double t = (-b - sqrt(discriminant)) / (2.0 * a);
    RayTracer::Math::Point3D hitPoint = ray.getOrigin() + ray.getDirection() * t;
    RayTracer::Math::Vector3D non_normal(
        (this->center - hitPoint).getX() * 2,
        (this->center - hitPoint).getY() * 2,
        (this->center - hitPoint).getZ() * 2
    );
    RayTracer::Math::Vector3D normal = non_normal.normalize();

    RayTracer::Render::Color newColor(0, 0, 0, this->color.getA());

    for (Lights::DirectionalLight light : lights) {
        double dot = std::max(0.0, normal.dot(light.getDirection()));
        double brightness = light.getBrightness();

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


void RayTracer::Primitives::Sphere::translate(Math::Vector3D vector)
{
    this->center = this->center + vector;
}

void RayTracer::Primitives::Sphere::rotateX(double angle)
{
    double radians = angle * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);
    double yPrime = cosA * this->center.getY() - sinA * this->center.getZ();
    double zPrime = sinA * this->center.getY() + cosA * this->center.getZ();
    this->center.setY(yPrime);
    this->center.setZ(zPrime);
}

void RayTracer::Primitives::Sphere::rotateY(double angle)
{
    double radians = angle * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);
    double xPrime = cosA * this->center.getX() + sinA * this->center.getZ();
    double zPrime = -sinA * this->center.getX() + cosA * this->center.getZ();
    this->center.setX(xPrime);
    this->center.setZ(zPrime);
}

void RayTracer::Primitives::Sphere::rotateZ(double angle)
{
    double radians = angle * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);
    double xPrime = cosA * this->center.getX() - sinA * this->center.getY();
    double yPrime = sinA * this->center.getX() + cosA * this->center.getY();
    this->center.setX(xPrime);
    this->center.setY(yPrime);
}

double RayTracer::Primitives::Sphere::getCenterX() const
{
    return this->center.getX();
}

double RayTracer::Primitives::Sphere::getCenterY() const
{
    return this->center.getY();
}

double RayTracer::Primitives::Sphere::getCenterZ() const
{
    return this->center.getZ();
}
