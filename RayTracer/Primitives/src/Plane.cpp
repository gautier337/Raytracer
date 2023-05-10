/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Rectangle
*/

#include "Plane.hpp"
#include <iostream>
#include <cmath>

RayTracer::Primitives::Plane::~Plane()
{
}

RayTracer::Primitives::Plane::Plane(
    std::string axis,
    double position,
    RayTracer::Render::Color color
) :
    axis(axis),
    position(position),
    color(color)
{
    if (this->axis == "X") {
        this->bottom_side = Math::Vector3D(10000, 0, 0);
        this->left_side = Math::Vector3D(0, 0, 10000);
        this->origin = Math::Point3D(0, 0, this->position);
    } else if (this->axis == "Y") {
        this->bottom_side = Math::Vector3D(10000, 0, 0);
        this->left_side = Math::Vector3D(0, 0, 10000);
        this->origin = Math::Point3D(this->position, 0, 0);
    } else if (this->axis == "Z") {
        this->bottom_side = Math::Vector3D(0, 10000, 10000);
        this->left_side = Math::Vector3D(0, 0, 0);
        this->origin = Math::Point3D(0, this->position, 0);
    }
}

RayTracer::Primitives::Plane::Plane(
    const RayTracer::Primitives::Plane &rectangle
) :
    axis(rectangle.axis),
    position(rectangle.position),
    color(rectangle.color),
    bottom_side(rectangle.bottom_side),
    left_side(rectangle.left_side),
    origin(rectangle.origin)
{
}

RayTracer::Primitives::Plane::Plane(
    RayTracer::Primitives::Plane &&rectangle
) :
    axis(rectangle.axis),
    position(rectangle.position),
    color(rectangle.color),
    bottom_side(rectangle.bottom_side),
    left_side(rectangle.left_side),
    origin(rectangle.origin)
{
}

RayTracer::Primitives::Plane &RayTracer::Primitives::Plane::operator=(
    const Plane &rectangle
)
{
    this->axis = rectangle.axis;
    this->position = rectangle.position;
    this->color = rectangle.color;
    this->bottom_side = rectangle.bottom_side;
    this->left_side = rectangle.left_side;
    this->origin = rectangle.origin;
    return *this;
}

RayTracer::Primitives::Plane &RayTracer::Primitives::Plane::operator=(
    Plane &&rectangle
)
{
    this->axis = rectangle.axis;
    this->position = rectangle.position;
    this->color = rectangle.color;
    this->bottom_side = rectangle.bottom_side;
    this->left_side = rectangle.left_side;
    this->origin = rectangle.origin;
    return *this;
}

double RayTracer::Primitives::Plane::getIntersectionPoint(View::Ray ray)
{
    Math::Vector3D normal;
    if (axis == "X") {
        normal = Math::Vector3D(1, 0, 0);
    } else if (axis == "Y") {
        normal = Math::Vector3D(0, 1, 0);
    } else {
        normal = Math::Vector3D(0, 0, 1);
    }
    if (normal.dot(ray.getDirection()) == 0) {
        return -1;
    }
    double t = (position - ray.getDirection().dot(normal)) / ray.getDirection().dot(normal);
    if (t < 0) {
        return -1;
    }
    return t;
}

bool RayTracer::Primitives::Plane::hits(View::Ray ray)
{
    double t = getIntersectionPoint(ray);
    if (t < 0) {
        return false;
    }
    Math::Point3D hitPoint = ray.getOrigin() + ray.getDirection() * t;
    Math::Vector3D normal;
    if (axis == "X") {
        normal = Math::Vector3D(1, 0, 0);
    } else if (axis == "Y") {
        normal = Math::Vector3D(0, 1, 0);
    } else {
        normal = Math::Vector3D(0, 0, 1);
    }
    if (normal.dot(ray.getDirection()) > 0) {
        normal = normal * -1;
    }
    return true;
}

RayTracer::Render::Color RayTracer::Primitives::Plane::computeColor(
    RayTracer::View::Ray ray,
    std::vector<std::unique_ptr<ILights>> &lights
)
{
    RayTracer::Render::Color newColor(0, 0, 0, 1);
    RayTracer::Math::Point3D origin = ray.getOrigin();

    if (!this->hits(ray))
        return newColor;

    RayTracer::Math::Vector3D normal = this->bottom_side.cross(this->left_side);
    normal.normalize();

    // Compute ambient color contribution
    RayTracer::Render::Color ambientColor(
        this->color.getR() * lights[0]->getBrightness(),
        this->color.getG() * lights[0]->getBrightness(),
        this->color.getB() * lights[0]->getBrightness(),
        this->color.getA()
    );
    newColor += ambientColor;

    // Compute directional light color contribution
    for (const auto &light : lights) {
        if (light->getDirection() != RayTracer::Math::Vector3D(0, 0, 0)) {
            RayTracer::Math::Vector3D lightDirection = light->getDirection();
            lightDirection.normalize();
            double dot = normal.dot(lightDirection);
            if (dot < 0)
                dot = 0;
            RayTracer::Render::Color lightColor(
                this->color.getR() * light->getBrightness() * dot,
                this->color.getG() * light->getBrightness() * dot,
                this->color.getB() * light->getBrightness() * dot,
                this->color.getA()
            );
            newColor += lightColor;
        }
    }
    return newColor;
}

RayTracer::Math::Point3D RayTracer::Primitives::Plane::pointAt(
    double u,
    double v
)
{
    if (u < 0 || u > 1 || v < 0 || v > 1)
        throw std::invalid_argument("u and v must be between 0 and 1");

    return this->origin + (this->bottom_side * u) + (this->left_side * v);
}

void RayTracer::Primitives::Plane::translate(
    RayTracer::Math::Vector3D translation
)
{
    return;
}

void RayTracer::Primitives::Plane::rotate(RayTracer::Math::Vector3D rotation, double angle)
{
    return;
}

void RayTracer::Primitives::Plane::scale(double factor)
{
    return;
}

std::string RayTracer::Primitives::Plane::getType() const {
    return "Plane";
}

RayTracer::Render::Color RayTracer::Primitives::Plane::getColor() const {
    return this->color;
}

void RayTracer::Primitives::Plane::setColor(RayTracer::Render::Color color) {
    this->color = color;
}

std::unique_ptr<RayTracer::IPrimitive> RayTracer::Primitives::Plane::clone() const
{
    return std::make_unique<RayTracer::Primitives::Plane>(*this);
}

extern "C" std::unique_ptr<RayTracer::Primitives::Plane> createPlane(
    std::string axis,
    double position,
    RayTracer::Render::Color color
)
{
    return std::make_unique<RayTracer::Primitives::Plane>(
        axis,
        position,
        color
    );
}
