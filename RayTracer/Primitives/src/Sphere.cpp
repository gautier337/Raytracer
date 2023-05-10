/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"
#include <cmath>

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
    if (discriminant < 0)
        return -1;
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

    if (oc.dot(ray.getDirection()) > 0)
        return false;
    double a = ray.getDirection().dot(ray.getDirection());
    double b = 2.0 * oc.dot(ray.getDirection());
    double c = oc.dot(oc) - this->radius * this->radius;
    double discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

RayTracer::Render::Color RayTracer::Primitives::Sphere::computeColor(
    RayTracer::View::Ray ray,
    std::vector<std::unique_ptr<ILights>> &lights,
    std::vector<std::unique_ptr<IPrimitive>> &primitives
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
        double brightness = light->getBrightness();
        if (light->getDirection() == RayTracer::Math::Vector3D(0, 0, 0)) {
            RayTracer::Render::Color lightColor(
                this->color.getR() * brightness,
                this->color.getG() * brightness,
                this->color.getB() * brightness,
                this->color.getA()
            );
            newColor += lightColor;
            continue;
        }

        RayTracer::Math::Vector3D lightDir = light->getDirection().normalize();
        double dot = std::max(0.0, -1 * normal.dot(lightDir));
        RayTracer::Render::Color lightColor(
            this->color.getR() * dot * brightness,
            this->color.getG() * dot * brightness,
            this->color.getB() * dot * brightness,
            this->color.getA()
        );

        newColor += lightColor;

        RayTracer::View::Ray shadowRay(hitPoint, light->getDirection());

        for (const auto &primitive : primitives) {
            if (primitive.get() == this)
                break;
            if (primitive->hits(shadowRay)) {
                RayTracer::Render::Color shadowColor(
                    -1 * lightColor.getR() * brightness,
                    -1 * lightColor.getG() * brightness,
                    -1 * lightColor.getB() * brightness,
                    -1 * lightColor.getA()
                );
                newColor += shadowColor;
                break;
            }
        }

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

std::string RayTracer::Primitives::Sphere::getType() const {
    return "Sphere";
}

RayTracer::Render::Color RayTracer::Primitives::Sphere::getColor() const {
    return this->color;
}

void RayTracer::Primitives::Sphere::setColor(RayTracer::Render::Color color) {
    this->color = color;
}

std::unique_ptr<RayTracer::IPrimitive> RayTracer::Primitives::Sphere::clone() const
{
    return std::make_unique<RayTracer::Primitives::Sphere>(*this);
}

extern "C" std::unique_ptr<RayTracer::Primitives::Sphere> createSphere(
    RayTracer::Math::Point3D center,
    double radius,
    RayTracer::Render::Color color
)
{
    return std::make_unique<RayTracer::Primitives::Sphere>(
        center,
        radius,
        color
    );
}
