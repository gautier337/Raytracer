/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Scene
*/

#include "Scene.hpp"
#include <algorithm>
#include <iostream>

RayTracer::Scene::Scene(const ParseConfig &config)
{
    auto &camera_config = config.get_setting("camera");
    if (camera_config.exists("position")) {
        double x = config.getDoubleFromSetting(camera_config["position"]["x"]);
        double y = config.getDoubleFromSetting(camera_config["position"]["y"]);
        double z = config.getDoubleFromSetting(camera_config["position"]["z"]);
        camera = View::Camera(
            Math::Point3D(x, y, z),
            Primitives::Rectangle3D(
                Math::Point3D(-0.5, -0.5, 1),
                Math::Vector3D(1, 0, 0),
                Math::Vector3D(0, 1, 0),
                Render::Color(0, 0, 0, 0)
            )
        );
    }
    auto &primitives = config.get_setting("primitives");
    if (primitives.exists("spheres")) {
        for (int i = 0; i < primitives["spheres"].getLength(); i++) {
            double x = config.getDoubleFromSetting(primitives["spheres"][i]["x"]);
            double y = config.getDoubleFromSetting(primitives["spheres"][i]["y"]);
            double z = config.getDoubleFromSetting(primitives["spheres"][i]["z"]);
            double radius = config.getDoubleFromSetting(primitives["spheres"][i]["r"]);

            Primitives::Sphere s(
                Math::Point3D(x, y, z),
                radius,
                Render::Color(
                    config.getDoubleFromSetting(primitives["spheres"][i]["color"]["r"]),
                    config.getDoubleFromSetting(primitives["spheres"][i]["color"]["g"]),
                    config.getDoubleFromSetting(primitives["spheres"][i]["color"]["b"]),
                    config.getDoubleFromSetting(primitives["spheres"][i]["color"]["a"])
                )
            );
            this->addObject(s);
        }
    }

    auto &lights_config = config.get_setting("lights");

    if (lights_config.exists("directional")) {
        for (int i = 0; i < lights_config["directional"].getLength(); i++) {
            double brightness = config.getDoubleFromSetting(lights_config["directional"][i]["brightness"]);
            double x_point = config.getDoubleFromSetting(lights_config["directional"][i]["point"]["x"]);
            double y_point = config.getDoubleFromSetting(lights_config["directional"][i]["point"]["y"]);
            double z_point = config.getDoubleFromSetting(lights_config["directional"][i]["point"]["z"]);
            double x_vector = config.getDoubleFromSetting(lights_config["directional"][i]["vector"]["x"]);
            double y_vector = config.getDoubleFromSetting(lights_config["directional"][i]["vector"]["y"]);
            double z_vector = config.getDoubleFromSetting(lights_config["directional"][i]["vector"]["z"]);

            Lights::DirectionalLight light(
                Math::Point3D(x_point, y_point, z_point),
                Math::Vector3D(-x_vector, -y_vector, -z_vector),
                brightness
            );
            this->addLight(light);
        }
    }

    Primitives::Rectangle3D ground(
        Math::Point3D(0, -5000, 0),
        Math::Vector3D(0, 10000, 10000),
        Math::Vector3D(0, 0, 0),
        Render::Color(1, 1, 0, 1)
    );
    this->addObject(ground);
}

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

RayTracer::View::Camera RayTracer::Scene::getCamera() const
{
    return this->camera;
}

void RayTracer::Scene::translateCamera(Math::Vector3D vector)
{
    View::Camera newCamera = this->getCamera();
    newCamera.translate(vector);
    this->setCamera(newCamera);
}

void RayTracer::Scene::rotateCamera(Math::Vector3D vector, double angle)
{
    View::Camera newCamera = this->getCamera();
    newCamera.rotate(vector, angle);
    this->setCamera(newCamera);
}
