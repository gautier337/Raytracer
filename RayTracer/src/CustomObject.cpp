/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** CustomObject
*/

#include "CustomObject.hpp"

RayTracer::CustomObject::CustomObject()
{
}

RayTracer::CustomObject::~CustomObject()
{
}

RayTracer::CustomObject::CustomObject(const CustomObject &customObject)
{
    for (const auto &primitive : customObject.primitives)
        this->primitives.emplace_back(primitive->clone());
}


RayTracer::CustomObject::CustomObject(CustomObject &&customObject)
{
    this->primitives = std::move(customObject.primitives);
}

RayTracer::CustomObject &RayTracer::CustomObject::operator=(
    const CustomObject &customObject
)
{
    for (const auto &primitive : customObject.primitives)
        this->primitives.emplace_back(primitive->clone());
    return *this;
}

RayTracer::CustomObject &RayTracer::CustomObject::operator=(
    CustomObject &&customObject
)
{
    this->primitives = std::move(customObject.primitives);
    return *this;
}

void RayTracer::CustomObject::addPrimitive(
    std::unique_ptr<IPrimitive> primitive
)
{
    this->primitives.push_back(std::move(primitive));
}

double RayTracer::CustomObject::getIntersectionPoint(View::Ray ray)
{
    double closestT = 0;
    double t = 0;

    for (auto &primitive : this->primitives) {
        t = primitive->getIntersectionPoint(ray);
        if (t > 0 && (closestT == 0 || t < closestT))
            closestT = t;
    }
    return closestT;
}

bool RayTracer::CustomObject::hits(View::Ray ray)
{
    for (auto &primitive : this->primitives) {
        if (primitive->hits(ray))
            return true;
    }
    return false;
}

RayTracer::Render::Color RayTracer::CustomObject::computeColor(
    View::Ray ray,
    std::vector<std::unique_ptr<ILights>> &lights
)
{
    Render::Color color;
    double closestT = 0;
    double t = 0;

    for (auto &primitive : this->primitives) {
        t = primitive->getIntersectionPoint(ray);
        if (t > 0 && (closestT == 0 || t < closestT)) {
            closestT = t;
            color = primitive->computeColor(ray, lights);
        }
    }
    return color;
}
