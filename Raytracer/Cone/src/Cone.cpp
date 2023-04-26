/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Cone3D
*/

#include "Cone.hpp"
#include <cmath>

RayTracer::Cone::Cone()
{
}

RayTracer::Cone::~Cone()
{
}

RayTracer::Cone::Cone(Math::Point3D center, Math::Vector3D axis, double base_radius, double apex_radius, double height) : center(center), axis(axis), base_radius(base_radius), apex_radius(apex_radius), height(height)
{
}

RayTracer::Cone::Cone(const Cone &cone) : center(cone.center), axis(cone.axis), base_radius(cone.base_radius), apex_radius(cone.apex_radius), height(cone.height)
{
}

RayTracer::Cone::Cone(Cone &&cone) : center(cone.center), axis(cone.axis), base_radius(cone.base_radius), apex_radius(cone.apex_radius), height(cone.height)
{
}

RayTracer::Cone &RayTracer::Cone::operator=(const Cone &cone)
{
    this->center = cone.center;
    this->axis = cone.axis;
    this->base_radius = cone.base_radius;
    this->apex_radius = cone.apex_radius;
    this->height = cone.height;
    return *this;
}

RayTracer::Cone &RayTracer::Cone::operator=(Cone &&cone)
{
    this->center = cone.center;
    this->axis = cone.axis;
    this->base_radius = cone.base_radius;
    this->apex_radius = cone.apex_radius;
    this->height = cone.height;
    return *this;
}

Math::Vector3D normalize(const Math::Vector3D& vec)
{
    double magnitude = sqrt(vec.getX() * vec.getX() + vec.getY() * vec.getY() + vec.getZ() * vec.getZ());
    return Math::Vector3D(vec.getX() / magnitude, vec.getY() / magnitude, vec.getZ() / magnitude);
}

bool RayTracer::Cone::hits(Ray ray)
{
    Math::Vector3D rayDirection = ray.getDirection();
    Math::Point3D rayOriginPoint = ray.getOrigin();

    Math::Vector3D rayOrigin(rayOriginPoint.getX(), rayOriginPoint.getY(), rayOriginPoint.getZ());
    Math::Vector3D coneOrigin(center.getX(), center.getY(), center.getZ());

    Math::Vector3D diff = rayOrigin - coneOrigin;
    Math::Vector3D axis_normalized = normalize(axis);

    double k = (base_radius - apex_radius) / height;
    double a = rayDirection.dot(rayDirection) - (1 + k * k) * pow(rayDirection.dot(axis_normalized), 2);
    double b = 2.0 * (rayDirection.dot(diff) - (1 + k * k) * rayDirection.dot(axis_normalized) * diff.dot(axis_normalized));
    double c = diff.dot(diff) - (1 + k * k) * pow(diff.dot(axis_normalized), 2);

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
    Math::Vector3D cone_to_intersection = intersection - coneOrigin;
    double projected_height = cone_to_intersection.dot(axis_normalized);

    return projected_height >= 0 && projected_height <= height;
}
