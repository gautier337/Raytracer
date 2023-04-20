/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

RayTracer::Sphere::Sphere() : center(), radius(0)
{
}

RayTracer::Sphere::~Sphere()
{
}

RayTracer::Sphere::Sphere(Math::Point3D center, double radius) : center(center), radius(radius)
{
}

RayTracer::Sphere::Sphere(const Sphere &sphere) : center(sphere.center), radius(sphere.radius)
{
}

RayTracer::Sphere::Sphere(Sphere &&sphere) : center(sphere.center), radius(sphere.radius)
{
}

RayTracer::Sphere &RayTracer::Sphere::operator=(const Sphere &sphere)
{
    this->center = sphere.center;
    this->radius = sphere.radius;
    return *this;
}

RayTracer::Sphere &RayTracer::Sphere::operator=(Sphere &&sphere)
{
    this->center = sphere.center;
    this->radius = sphere.radius;
    return *this;
}
#include <iostream>
bool RayTracer::Sphere::hits(Ray ray)
{
    Math::Vector3D oc((ray.getOrigin() - this->center).getX(), (ray.getOrigin() - this->center).getY(), (ray.getOrigin() - this->center).getZ());
    //std::cout << "---------------DEBUG------------" << std::endl;
    //std::cout << "|" << "Ray origin: {x: " << ray.getOrigin().getX() << " y: " << ray.getOrigin().getY() << " z: " << ray.getOrigin().getZ() << "}" << std::endl;
    //std::cout << "|" << "Ray direction: {x: " << ray.getDirection().getX() << " y: " << ray.getDirection().getY() << " z: " << ray.getDirection().getZ() << "}" << std::endl;
    //std::cout << "|" << "OC: {x: " << oc.getX() << " y: " << oc.getY() << " z: " << oc.getZ() << "}" << std::endl;
    //std::cout << "|--------------------------------" << std::endl;

    double a = ray.getDirection().dot(ray.getDirection());
    double b = 2.0 * oc.dot(ray.getDirection());
    double c = oc.dot(oc) - this->radius * this->radius;
    double discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}
