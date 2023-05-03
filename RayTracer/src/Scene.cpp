/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Scene
*/

#include "Scene.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include <algorithm>
#include <iostream>

RayTracer::Scene::Scene(const ParseConfig &config) :
    factory()
{
    auto &camera_config = config.get_setting("camera");
    if (camera_config.exists("position")) {
        double x = config.getDoubleFromSetting(camera_config["position"]["x"]);
        double y = config.getDoubleFromSetting(camera_config["position"]["y"]);
        double z = config.getDoubleFromSetting(camera_config["position"]["z"]);
        std::unique_ptr<Math::Point3D> position = this->factory.createPlugin<Math::Point3D>("Point3D", x, y, z);
        std::unique_ptr<Math::Point3D> origin = this->factory.createPlugin<Math::Point3D>("Point3D", -0.5, -0.5, 1);
        std::unique_ptr<Math::Vector3D> bottom_side = this->factory.createPlugin<Math::Vector3D>("Vector3D", 1, 0, 0);
        std::unique_ptr<Math::Vector3D> left_side = this->factory.createPlugin<Math::Vector3D>("Vector3D", 0, 1, 0);
        std::unique_ptr<Render::Color> color = this->factory.createPlugin<Render::Color>("Color", 0, 0, 0, 0);
        std::unique_ptr<Primitives::Rectangle3D> screen = this->factory.createPlugin<Primitives::Rectangle3D>(
            "Rectangle3D",
            *origin,
            *bottom_side,
            *left_side,
            *color
        );
        this->camera = this->factory.createPlugin<View::Camera>("Camera", *position, *screen);
    }

    auto &primitives = config.get_setting("primitives");
    if (primitives.exists("spheres")) {
        for (int i = 0; i < primitives["spheres"].getLength(); i++) {
            double x = config.getDoubleFromSetting(primitives["spheres"][i]["x"]);
            double y = config.getDoubleFromSetting(primitives["spheres"][i]["y"]);
            double z = config.getDoubleFromSetting(primitives["spheres"][i]["z"]);
            std::unique_ptr<Math::Point3D> position = this->factory.createPlugin<Math::Point3D>("Point3D", x, y, z);
            double radius = config.getDoubleFromSetting(primitives["spheres"][i]["r"]);
            std::unique_ptr<Render::Color> primitiveColor = this->factory.createPlugin<Render::Color>(
                "Color",
                config.getDoubleFromSetting(primitives["spheres"][i]["color"]["r"]),
                config.getDoubleFromSetting(primitives["spheres"][i]["color"]["g"]),
                config.getDoubleFromSetting(primitives["spheres"][i]["color"]["b"]),
                config.getDoubleFromSetting(primitives["spheres"][i]["color"]["a"])
            );

            std::unique_ptr<Primitives::Sphere> sphere = this->factory.createPlugin<Primitives::Sphere>(
                "Sphere",
                *position,
                radius,
                *primitiveColor
            );
            this->addPrimitive(std::make_shared<Primitives::Sphere>(*sphere));
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
            std::unique_ptr<Math::Point3D> origin = this->factory.createPlugin<Math::Point3D>("Point3D", x_point, y_point, z_point);
            std::unique_ptr<Math::Vector3D> direction = this->factory.createPlugin<Math::Vector3D>("Vector3D", -x_vector, y_vector, z_vector);
            std::unique_ptr<Render::Color> lightColor = this->factory.createPlugin<Render::Color>(
                "Color",
                config.getDoubleFromSetting(lights_config["directional"][i]["color"]["r"]),
                config.getDoubleFromSetting(lights_config["directional"][i]["color"]["g"]),
                config.getDoubleFromSetting(lights_config["directional"][i]["color"]["b"]),
                config.getDoubleFromSetting(lights_config["directional"][i]["color"]["a"])
            );

            std::unique_ptr<Lights::DirectionalLight> light = this->factory.createPlugin<Lights::DirectionalLight>(
                "DirectionalLight",
                *origin,
                *direction,
                brightness,
                *lightColor
            );
            this->addLight(std::make_shared<Lights::DirectionalLight>(*light));
        }
    }

    std::unique_ptr<Math::Point3D> origin = this->factory.createPlugin<Math::Point3D>("Point3D", 0, -5000, 0);
    std::unique_ptr<Math::Vector3D> bottom_side = this->factory.createPlugin<Math::Vector3D>("Vector3D", 0, 10000, 10000);
    std::unique_ptr<Math::Vector3D> left_side = this->factory.createPlugin<Math::Vector3D>("Vector3D", 0, 0, 0);
    std::unique_ptr<Render::Color> color = this->factory.createPlugin<Render::Color>("Color", 1, 1, 0, 1);
    std::unique_ptr<Primitives::Rectangle3D> ground = this->factory.createPlugin<Primitives::Rectangle3D>(
        "Rectangle3D",
        *origin,
        *bottom_side,
        *left_side,
        *color
    );
    this->addPrimitive(std::make_shared<Primitives::Rectangle3D>(*ground));
}

RayTracer::Scene::Scene() :
    factory()
{
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

void RayTracer::Scene::setCamera(std::unique_ptr<View::Camera> camera)
{
    this->camera = std::move(camera);
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
            View::Ray ray = camera->ray(x, y);
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

RayTracer::View::Camera RayTracer::Scene::getCamera() const
{
    return *this->camera;
}

void RayTracer::Scene::translateCamera(Math::Vector3D vector)
{
    View::Camera newCamera = this->getCamera();
    newCamera.translate(vector);
    this->setCamera(std::make_unique<View::Camera>(newCamera));
}

void RayTracer::Scene::rotateCamera(Math::Vector3D vector, double angle)
{
    View::Camera newCamera = this->getCamera();
    newCamera.rotate(vector, angle);
    this->setCamera(std::make_unique<View::Camera>(newCamera));
}

RayTracer::Factory RayTracer::Scene::getFactory() const
{
    return this->factory;
}
