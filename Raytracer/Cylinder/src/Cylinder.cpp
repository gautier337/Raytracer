/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Cylinder
*/

#include "../include/Cylinder.hpp"
#include <cmath>

RayTracer::Cylinder::Cylinder()
{
}

RayTracer::Cylinder::~Cylinder()
{
}

RayTracer::Cylinder::Cylinder(Math::Point3D center, Math::Vector3D axis, double radius, double height) : center(center), axis(axis), radius(radius), height(height)
{
}


RayTracer::Cylinder::Cylinder(const Cylinder &cylinder) : center(cylinder.center), axis(cylinder.axis), radius(cylinder.radius), height(cylinder.height)
{
}

RayTracer::Cylinder::Cylinder(Cylinder &&cylinder) : center(cylinder.center), axis(cylinder.axis), radius(cylinder.radius), height(cylinder.height)
{
}

RayTracer::Cylinder &RayTracer::Cylinder::operator=(const Cylinder &cylinder)
{
    this->center = cylinder.center;
    this->axis = cylinder.axis;
    this->radius = cylinder.radius;
    this->height = cylinder.height;
    return *this;
}

RayTracer::Cylinder &RayTracer::Cylinder::operator=(Cylinder &&cylinder)
{
    this->center = cylinder.center;
    this->axis = cylinder.axis;
    this->radius = cylinder.radius;
    this->height = cylinder.height;
    return *this;
}

Math::Vector3D normalize(const Math::Vector3D& vec)
{
    double magnitude = sqrt(vec.getX() * vec.getX() + vec.getY() * vec.getY() + vec.getZ() * vec.getZ());
    return Math::Vector3D(vec.getX() / magnitude, vec.getY() / magnitude, vec.getZ() / magnitude);
}

bool RayTracer::Cylinder::hits(Ray ray)
{
    Math::Vector3D rayDirection = ray.getDirection();
    Math::Point3D rayOriginPoint = ray.getOrigin();

    Math::Vector3D rayOrigin(rayOriginPoint.getX(), rayOriginPoint.getY(), rayOriginPoint.getZ());
    Math::Vector3D cylinderOrigin(center.getX(), center.getY(), center.getZ());

    Math::Vector3D diff = rayOrigin - cylinderOrigin;
    Math::Vector3D axis_normalized = normalize(axis);

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

    Math::Vector3D intersection = rayOrigin + rayDirection * t0;
    Math::Vector3D cylinder_to_intersection = intersection - cylinderOrigin;
    double projected_height = cylinder_to_intersection.dot(axis_normalized);

    return projected_height >= 0 && projected_height <= height;
}
