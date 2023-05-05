/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"
#include <iostream>
#include <cmath>

RayTracer::Primitives::Cylinder::Cylinder()
{
}

RayTracer::Primitives::Cylinder::~Cylinder()
{
}

RayTracer::Primitives::Cylinder::Cylinder(
    RayTracer::Math::Point3D center,
    RayTracer::Math::Vector3D axis,
    double radius,
    double height,
    RayTracer::Render::Color color
) : 
    center(center),
    axis(axis),
    radius(radius),
    height(height),
    color(color)
{
}

RayTracer::Primitives::Cylinder::Cylinder(const Cylinder &cylinder) :
    center(cylinder.center),
    axis(cylinder.axis),
    radius(cylinder.radius),
    height(cylinder.height),
    color(cylinder.color)
{
}

RayTracer::Primitives::Cylinder::Cylinder(Cylinder &&cylinder) :
    center(cylinder.center),
    axis(cylinder.axis),
    radius(cylinder.radius),
    height(cylinder.height),
    color(cylinder.color)
{
}

RayTracer::Primitives::Cylinder &RayTracer::Primitives::Cylinder::operator=(const Cylinder &cylinder)
{
    this->center = cylinder.center;
    this->axis = cylinder.axis;
    this->radius = cylinder.radius;
    this->height = cylinder.height;
    this->color = cylinder.color;
    return *this;
}

RayTracer::Primitives::Cylinder &RayTracer::Primitives::Cylinder::operator=(Cylinder &&cylinder)
{
    this->center = cylinder.center;
    this->axis = cylinder.axis;
    this->radius = cylinder.radius;
    this->height = cylinder.height;
    this->color = cylinder.color;
    return *this;
}

RayTracer::Math::Vector3D normalize(const RayTracer::Math::Vector3D& vec)
{
    double magnitude = sqrt(vec.getX() * vec.getX() + vec.getY() * vec.getY() + vec.getZ() * vec.getZ());
    return RayTracer::Math::Vector3D(vec.getX() / magnitude, vec.getY() / magnitude, vec.getZ() / magnitude);
}

bool RayTracer::Primitives::Cylinder::hits(View::Ray ray)
{
    RayTracer::Math::Vector3D rayDirection = ray.getDirection();
    RayTracer::Math::Point3D rayOriginPoint = ray.getOrigin();

    RayTracer::Math::Vector3D rayOrigin(rayOriginPoint.getX(), rayOriginPoint.getY(), rayOriginPoint.getZ());
    RayTracer::Math::Vector3D cylinderOrigin(center.getX(), center.getY(), center.getZ());

    RayTracer::Math::Vector3D diff = rayOrigin - cylinderOrigin;
    RayTracer::Math::Vector3D axis_normalized = normalize(axis);

    double a = rayDirection.dot(rayDirection) - pow(rayDirection.dot(axis_normalized), 2);
    double b = 2.0 * (rayDirection.dot(diff) - (rayDirection.dot(axis_normalized) * diff.dot(axis_normalized)));
    double c = diff.dot(diff) - pow(diff.dot(axis_normalized), 2) - pow(radius, 2);

    double discriminant = pow(b, 2) - 4 * a * c;

    if (discriminant < 0)
        return false;

    double t0 = (-b - sqrt(discriminant)) / (2 * a);
    double t1 = (-b + sqrt(discriminant)) / (2 * a);

    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0) return false;
    }

    RayTracer::Math::Vector3D intersection = rayOrigin + rayDirection * t0;
    RayTracer::Math::Vector3D cylinder_to_intersection = intersection - cylinderOrigin;
    double projected_height = cylinder_to_intersection.dot(axis_normalized);

    return projected_height >= 0 && projected_height <= height;
}

RayTracer::Render::Color RayTracer::Primitives::Cylinder::computeColor(
    RayTracer::View::Ray ray,
    std::vector<std::unique_ptr<ILights>> &lights
)
{
    RayTracer::Render::Color newColor(0, 0, 0, this->color.getA());
    RayTracer::Math::Point3D intersectionPoint = ray.getOrigin() + ray.getDirection() * closestT;

    RayTracer::Math::Vector3D cylinder_to_intersection = RayTracer::Math::Vector3D(
        intersectionPoint.getX(),
        intersectionPoint.getY(),
        intersectionPoint.getZ()
    ) - RayTracer::Math::Vector3D(
        center.getX(),
        center.getY(),
        center.getZ()
    );
    double projected_height = cylinder_to_intersection.dot(axis.normalize());
    RayTracer::Math::Vector3D base_point = RayTracer::Math::Vector3D(
        center.getX(),
        center.getY(),
        center.getZ()
    ) + axis.normalize() * projected_height;
    RayTracer::Math::Vector3D normal = RayTracer::Math::Vector3D(
        intersectionPoint.getX(),
        intersectionPoint.getY(),
        intersectionPoint.getZ()
    ) - base_point;
    normal = normal.normalize();

    for (auto &light : lights) {
        RayTracer::Math::Vector3D lightDirection = light->getDirection();
        RayTracer::Math::Vector3D lightDirectionNormalized = lightDirection.normalize();

        if (light->getDirection() == RayTracer::Math::Vector3D(0, 0, 0)) {
            RayTracer::Render::Color lightColor(
                this->color.getR() * light->getBrightness(),
                this->color.getG() * light->getBrightness(),
                this->color.getB() * light->getBrightness(),
                this->color.getA()
            );

            newColor += lightColor;
        }

        double dot = std::max(0.0, normal.dot(lightDirectionNormalized));
        double brightness = light->getBrightness();

        RayTracer::Render::Color lightColor(
            this->color.getR() * dot * brightness,
            this->color.getG() * dot * brightness,
            this->color.getB() * dot * brightness,
            this->color.getA()
        );

        newColor += lightColor;
    }

    return newColor;
}

void RayTracer::Primitives::Cylinder::translate(RayTracer::Math::Vector3D translation)
{
    this->center = this->center + translation;
}

void RayTracer::Primitives::Cylinder::rotate(Math::Vector3D axis, double angle)
{
    return;
}

void RayTracer::Primitives::Cylinder::scale(double factor)
{
    return;
}

double RayTracer::Primitives::Cylinder::getIntersectionPoint(View::Ray ray)
{
    RayTracer::Math::Vector3D rayDirection = ray.getDirection();
    RayTracer::Math::Point3D rayOriginPoint = ray.getOrigin();

    RayTracer::Math::Vector3D rayOrigin(rayOriginPoint.getX(), rayOriginPoint.getY(), rayOriginPoint.getZ());
    RayTracer::Math::Vector3D cylinderOrigin(center.getX(), center.getY(), center.getZ());

    RayTracer::Math::Vector3D diff = rayOrigin - cylinderOrigin;
    RayTracer::Math::Vector3D axis_normalized = normalize(axis);

    double a = rayDirection.dot(rayDirection) - pow(rayDirection.dot(axis_normalized), 2);
    double b = 2.0 * (rayDirection.dot(diff) - (rayDirection.dot(axis_normalized) * diff.dot(axis_normalized)));
    double c = diff.dot(diff) - pow(diff.dot(axis_normalized), 2) - pow(radius, 2);

    double discriminant = pow(b, 2) - 4 * a * c;

    if (discriminant < 0)
        return -1;

    double t0 = (-b - sqrt(discriminant)) / (2 * a);
    double t1 = (-b + sqrt(discriminant)) / (2 * a);

    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0) return -1;
    }

    RayTracer::Math::Vector3D intersection = rayOrigin + rayDirection * t0;
    RayTracer::Math::Vector3D cylinder_to_intersection = intersection - cylinderOrigin;
    double projected_height = cylinder_to_intersection.dot(axis_normalized);

    if (projected_height >= 0 && projected_height <= height) {
        return t0;
    } else {
        return -1;
    }
}

std::string RayTracer::Primitives::Cylinder::getType() const
{
    return "Cylinder";
};

RayTracer::Render::Color RayTracer::Primitives::Cylinder::getColor() const
{
    return this->color;
}

void RayTracer::Primitives::Cylinder::setColor(RayTracer::Render::Color color)
{
    this->color = color;
};

std::unique_ptr<RayTracer::IPrimitive> RayTracer::Primitives::Cylinder::clone() const
{
    return std::make_unique<RayTracer::Primitives::Cylinder>(*this);
}

extern "C" std::unique_ptr<RayTracer::Primitives::Cylinder> createCylinder(
    RayTracer::Math::Point3D center,
    RayTracer::Math::Vector3D axis,
    double radius,
    double height,
    RayTracer::Render::Color color
)
{
    return std::make_unique<RayTracer::Primitives::Cylinder>(
        center,
        axis,
        radius,
        height,
        color
    );
}