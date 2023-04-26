/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Scene
*/

#include "Scene.hpp"
#include <algorithm>

RayTracer::Scene::Scene()
    : camera(
        Math::Point3D(0, 0, 0),
        Primitives::Rectangle3D(
            Math::Point3D(-0.5, -0.5, 1),
            Math::Vector3D(1, 0, 0),
            Math::Vector3D(0, 1, 0),
            Render::Color(0, 0, 0, 0)
        )
    )
{
    Primitives::Sphere s(
        Math::Point3D(0, 0, 4),
        1,
        Render::Color(1, 0, 0, 1)
    );
    this->addObject(s);

    Primitives::Sphere s2(
        Math::Point3D(-1, 0, 4),
        0.5,
        Render::Color(0, 1, 0, 1)
    );
    this->addObject(s2);

    Primitives::Rectangle3D ground(
        Math::Point3D(0, -5000, 0),
        Math::Vector3D(0, 10000, 10000),
        Math::Vector3D(0, 0, 0),
        Render::Color(1, 1, 0, 1)
    );
    this->addObject(ground);

    Lights::DirectionalLight lightRight(
        Math::Point3D(0.5, 0.5, 4),
        Math::Vector3D(-0.5, -0.5, 0),
        0.25
    );
    this->addLight(lightRight);

    Lights::DirectionalLight lightLeft(
        Math::Point3D(-0.5, 0.5, 4),
        Math::Vector3D(0.5, -0.5, 0),
        1
    );
    this->addLight(lightLeft);
}

RayTracer::Scene::~Scene()
{
}

void RayTracer::Scene::addObject(Primitives::Rectangle3D object)
{
    rectangles.push_back(object);
}

void RayTracer::Scene::addObject(Primitives::Sphere object)
{
    spheres.push_back(object);
}

void RayTracer::Scene::addLight(Lights::DirectionalLight light)
{
    lights.push_back(light);
}

void RayTracer::Scene::setCamera(View::Camera camera)
{
    this->camera = camera;
}

std::vector<std::vector<RayTracer::Render::Color>> RayTracer::Scene::getPixels() const
{
    return this->pixels;
}

void RayTracer::Scene::render(int pixelSize, int width, int height)
{
    int index = 0;

    this->pixels = std::vector
        <std::vector<Render::Color>>(
            height,
            std::vector<Render::Color>(width)
    );

    for (double y = 1; y >= 0; y -= static_cast<double>(pixelSize) / height) {
        for (double x = 0; x < 1; x += static_cast<double>(pixelSize) / width) {
            Render::Color color(0, 0, 0, 1);
            View::Ray ray = camera.ray(x, y);
            auto sortedRectangles = rectangles;
            auto sortedSpheres = spheres;

            std::sort(sortedSpheres.begin(), sortedSpheres.end(), [&ray](Primitives::Sphere &a, Primitives::Sphere &b) {
                return a.getCenterZ() > b.getCenterZ();
            });

            for (auto rectangle : sortedRectangles) {
                if (rectangle.hits(ray)) {
                    color = rectangle.computeColor(ray);
                }
            }

            for (auto sphere : sortedSpheres) {
                if (sphere.hits(ray)) {
                    color = sphere.computeColor(ray, this->lights);
                }
            }

            this->pixels[index / height][index % height] = color;
            index++;
        }
    }
}
