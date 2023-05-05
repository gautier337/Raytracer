/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** Cone3D
*/

#include "Cone.hpp"
#include <iostream>
#include <cmath>

RayTracer::Primitives::Cone::Cone()
{
}

RayTracer::Primitives::Cone::~Cone()
{
}

RayTracer::Primitives::Cone::Cone(
    RayTracer::Math::Point3D center,
    RayTracer::Math::Vector3D axis,
    double base_radius,
    double apex_radius,
    double height,
    RayTracer::Render::Color color
) :
    center(center),
    axis(axis),
    base_radius(base_radius),
    apex_radius(apex_radius),
    height(height),
    color(color)
{
}

RayTracer::Primitives::Cone::Cone(const Cone &cone) :
    center(cone.center),
    axis(cone.axis),
    base_radius(cone.base_radius),
    apex_radius(cone.apex_radius),
    height(cone.height),
    color(cone.color)
{
}

RayTracer::Primitives::Cone::Cone(Cone &&cone) :
    center(cone.center),
    axis(cone.axis),
    base_radius(cone.base_radius),
    apex_radius(cone.apex_radius),
    height(cone.height),
    color(cone.color)
{
}

RayTracer::Primitives::Cone &RayTracer::Primitives::Cone::operator=(const Cone &cone)
{
    this->center = cone.center;
    this->axis = cone.axis;
    this->base_radius = cone.base_radius;
    this->apex_radius = cone.apex_radius;
    this->height = cone.height;
    this->color = cone.color;
    return *this;
}

RayTracer::Primitives::Cone &RayTracer::Primitives::Cone::operator=(Cone &&cone)
{
    this->center = cone.center;
    this->axis = cone.axis;
    this->base_radius = cone.base_radius;
    this->apex_radius = cone.apex_radius;
    this->height = cone.height;
    this->color = cone.color;
    return *this;
}

RayTracer::Math::Vector3D normalize(const RayTracer::Math::Vector3D& vec)
{
    double magnitude = sqrt(vec.getX() * vec.getX() + vec.getY() * vec.getY() + vec.getZ() * vec.getZ());
    return RayTracer::Math::Vector3D(vec.getX() / magnitude, vec.getY() / magnitude, vec.getZ() / magnitude);
}

bool RayTracer::Primitives::Cone::hits(View::Ray ray)
{
    RayTracer::Math::Vector3D rayDirection = ray.getDirection();
    RayTracer::Math::Point3D rayOriginPoint = ray.getOrigin();

    RayTracer::Math::Vector3D rayOrigin(rayOriginPoint.getX(), rayOriginPoint.getY(), rayOriginPoint.getZ());
    RayTracer::Math::Vector3D coneOrigin(center.getX(), center.getY(), center.getZ());

    RayTracer::Math::Vector3D diff = rayOrigin - coneOrigin;
    RayTracer::Math::Vector3D axis_normalized = normalize(axis);

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
        if (t0 < 0)
            return false;
    }

    RayTracer::Math::Vector3D intersection = rayOrigin + rayDirection * t0;
    RayTracer::Math::Vector3D cone_to_intersection = intersection - coneOrigin;
    double projected_height = cone_to_intersection.dot(axis_normalized);

    bool within_cone_height = projected_height >= 0 && projected_height <= height;

    RayTracer::Math::Vector3D base_center = coneOrigin + axis_normalized * height;
    double plane_d = -(axis_normalized.dot(base_center));
    double t_base = -(rayOrigin.dot(axis_normalized) + plane_d) / rayDirection.dot(axis_normalized);

    if (t_base < 0) {
        return within_cone_height;
    }

    RayTracer::Math::Vector3D intersection_base = rayOrigin + rayDirection * t_base;
    RayTracer::Math::Vector3D base_to_intersection_base = intersection_base - base_center;
    double distance_to_base_center = base_to_intersection_base.length();
    bool within_base_radius = distance_to_base_center <= base_radius;

    return within_cone_height || within_base_radius;
}

RayTracer::Render::Color RayTracer::Primitives::Cone::computeColor(
    RayTracer::View::Ray ray,
    std::vector<std::unique_ptr<ILights>> &lights
)
{
    RayTracer::Math::Point3D hitPoint = ray.getOrigin() + ray.getDirection() * this->closestT;
    RayTracer::Math::Vector3D hitPointToCenter = RayTracer::Math::Vector3D(hitPoint.getX() - this->center.getX(), hitPoint.getY() - this->center.getY(), hitPoint.getZ() - this->center.getZ());
    RayTracer::Math::Vector3D non_normal = hitPointToCenter - (this->axis.normalize() * hitPointToCenter.dot(this->axis.normalize()));
    RayTracer::Math::Vector3D normal = non_normal.normalize();

    RayTracer::Render::Color newColor(0, 0, 0, this->color.getA());

    for (const auto &light : lights) {
        if (light->getDirection() == RayTracer::Math::Vector3D(0, 0, 0)) {
            RayTracer::Render::Color lightColor(
                this->color.getR() * light->getBrightness(),
                this->color.getG() * light->getBrightness(),
                this->color.getB() * light->getBrightness(),
                this->color.getA()
            );
            newColor += lightColor;
        }
        RayTracer::Math::Vector3D lightDir = light->getDirection().normalize();
        double dot = std::max(0.0, normal.dot(lightDir));
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

void RayTracer::Primitives::Cone::translate(RayTracer::Math::Vector3D translation)
{
    this->center = this->center + translation;
}

void RayTracer::Primitives::Cone::rotate(RayTracer::Math::Vector3D axis, double angle)
{
    return;
}

void RayTracer::Primitives::Cone::scale(double factor)
{
    return;
}

double RayTracer::Primitives::Cone::getIntersectionPoint(View::Ray ray)
{
    RayTracer::Math::Vector3D rayDirection = ray.getDirection();
    RayTracer::Math::Point3D rayOriginPoint = ray.getOrigin();

    RayTracer::Math::Vector3D rayOrigin(rayOriginPoint.getX(), rayOriginPoint.getY(), rayOriginPoint.getZ());
    RayTracer::Math::Vector3D coneOrigin(center.getX(), center.getY(), center.getZ());

    RayTracer::Math::Vector3D diff = rayOrigin - coneOrigin;
    RayTracer::Math::Vector3D axis_normalized = normalize(axis);

    double k = (base_radius - apex_radius) / height;
    double a = rayDirection.dot(rayDirection) - (1 + k * k) * pow(rayDirection.dot(axis_normalized), 2);
    double b = 2.0 * (rayDirection.dot(diff) - (1 + k * k) * rayDirection.dot(axis_normalized) * diff.dot(axis_normalized));
    double c = diff.dot(diff) - (1 + k * k) * pow(diff.dot(axis_normalized), 2);

    double discriminant = pow(b, 2) - 4 * a * c;

    if (discriminant < 0)
        return -1;

    double t0 = (-b - sqrt(discriminant)) / (2 * a);
    double t1 = (-b + sqrt(discriminant)) / (2 * a);

    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0)
            return -1;
    }

    RayTracer::Math::Vector3D intersection = rayOrigin + rayDirection * t0;
    RayTracer::Math::Vector3D cone_to_intersection = intersection - coneOrigin;
    double projected_height = cone_to_intersection.dot(axis_normalized);

    if (projected_height >= 0 && projected_height <= height) {
        return t0;
    } else {
        return -1;
    }
}

std::string RayTracer::Primitives::Cone::getType() const
{
    return "Cone";
};

RayTracer::Render::Color RayTracer::Primitives::Cone::getColor() const
{
    return this->color;
}

void RayTracer::Primitives::Cone::setColor(RayTracer::Render::Color color)
{
    this->color = color;
};

extern "C" std::unique_ptr<RayTracer::Primitives::Cone> createCone(
    RayTracer::Math::Point3D center,
    RayTracer::Math::Vector3D axis,
    double base_radius,
    double apex_radius,
    double height,
    RayTracer::Render::Color color
)
{
    return std::make_unique<RayTracer::Primitives::Cone>(
        center,
        axis,
        base_radius,
        apex_radius,
        height,
        color
    );
}
