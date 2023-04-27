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
            Render::Color primitiveColor(
                config.getDoubleFromSetting(primitives["spheres"][i]["color"]["r"]),
                config.getDoubleFromSetting(primitives["spheres"][i]["color"]["g"]),
                config.getDoubleFromSetting(primitives["spheres"][i]["color"]["b"]),
                config.getDoubleFromSetting(primitives["spheres"][i]["color"]["a"])
            );

            this->addPrimitive(std::make_shared<Primitives::Sphere>(
                Math::Point3D(x, y, z),
                radius,
                primitiveColor
            ));
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
            Render::Color lightColor(
                config.getDoubleFromSetting(lights_config["directional"][i]["color"]["r"]),
                config.getDoubleFromSetting(lights_config["directional"][i]["color"]["g"]),
                config.getDoubleFromSetting(lights_config["directional"][i]["color"]["b"]),
                config.getDoubleFromSetting(lights_config["directional"][i]["color"]["a"])
            );

            this->addLight(std::make_shared<Lights::DirectionalLight>(
                Math::Point3D(x_point, y_point, z_point),
                Math::Vector3D(-x_vector, -y_vector, -z_vector),
                brightness,
                lightColor)
            );
        }
    }

    this->addPrimitive(std::make_shared<Primitives::Rectangle3D>(
        Math::Point3D(0, -5000, 0),
        Math::Vector3D(0, 10000, 10000),
        Math::Vector3D(0, 0, 0),
        Render::Color(1, 1, 0, 1)
    ));
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
    this->addPrimitive(std::make_shared<Primitives::Sphere>(
        Math::Point3D(0, 0, 4),
        1,
        Render::Color(1, 0, 0, 1)
    ));

    this->addPrimitive(std::make_shared<Primitives::Sphere>(
        Math::Point3D(-1, 0, 4),
        0.5,
        Render::Color(0, 1, 0, 1)
    ));

    this->addPrimitive(std::make_shared<Primitives::Rectangle3D>(
        Math::Point3D(0, -5000, 0),
        Math::Vector3D(0, 10000, 10000),
        Math::Vector3D(0, 0, 0),
        Render::Color(1, 1, 0, 1)
    ));

    this->addLight(std::make_shared<Lights::DirectionalLight>(
        Math::Point3D(0.5, 0.5, 4),
        Math::Vector3D(-0.5, -0.5, 0),
        0.25,
        Render::Color(1, 1, 1, 1)
    ));

    this->addLight(std::make_shared<Lights::DirectionalLight>(
        Math::Point3D(-0.5, 0.5, 4),
        Math::Vector3D(0.5, -0.5, 0),
        1,
        Render::Color(1, 1, 1, 1)
    ));
}

RayTracer::Scene::~Scene()
{
}

void RayTracer::Scene::addPrimitive(std::shared_ptr<IPrimitives> primitive)
{
    this->primitives.push_back(primitive);
}

void RayTracer::Scene::addLight(std::shared_ptr<ILights> light)
{
    this->lights.push_back(std::move(light));
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
            auto sortedPrimitives = primitives;

            std::sort(sortedPrimitives.begin(), sortedPrimitives.end(), [&ray](
                std::shared_ptr<IPrimitives> a, std::shared_ptr<IPrimitives> b) {
                return a->getIntersectionPoint(ray) < b->getIntersectionPoint(ray);
            });

            for (std::shared_ptr<IPrimitives> primitive : sortedPrimitives) {
                if (primitive->hits(ray)) {
                    color = primitive->computeColor(ray, lights);
                    break;
                }
            }

            this->pixels[index / height][index % height] = color;
            index++;
        }
    }
}
