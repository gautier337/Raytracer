/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Scene
*/

#include "Scene.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "Cone.hpp"
#include "Signatures.hpp"
#include <algorithm>
#include <iostream>
#include <limits>

RayTracer::Scene::Scene(const ParseConfig &config) :
    factory()
{
    try {
        auto &camera_config = config.get_setting("camera");
        if (camera_config.exists("position")) {
            double x = config.getDoubleFromSetting(camera_config["position"]["x"]);
            double y = config.getDoubleFromSetting(camera_config["position"]["y"]);
            double z = config.getDoubleFromSetting(camera_config["position"]["z"]);
            std::unique_ptr<Math::Point3D> position = this->factory.createPlugin<Point3DSignature>("Point3D", x, y, z);
            std::unique_ptr<Math::Point3D> origin = this->factory.createPlugin<Point3DSignature>("Point3D", -0.5, -0.5, 1);
            std::unique_ptr<Math::Vector3D> bottom_side = this->factory.createPlugin<Vector3DSignature>("Vector3D", 1, 0, 0);
            std::unique_ptr<Math::Vector3D> left_side = this->factory.createPlugin<Vector3DSignature>("Vector3D", 0, 1, 0);
            std::unique_ptr<Render::Color> color = this->factory.createPlugin<ColorSignature>("Color", 0, 0, 0, 0);
            std::unique_ptr<Primitives::Rectangle3D> screen = this->factory.createPlugin<Rectangle3DSignature>(
                "Rectangle3D",
                *origin,
                *bottom_side,
                *left_side,
                *color
            );
            this->camera = this->factory.createPlugin<CameraSignature>("Camera", *position, *screen);
            this->original_camera = this->factory.createPlugin<CameraSignature>("Camera", *position, *screen);
        }

        auto &primitives = config.get_setting("primitives");
        if (primitives.exists("spheres")) {
            for (int i = 0; i < primitives["spheres"].getLength(); i++) {
                double x = config.getDoubleFromSetting(primitives["spheres"][i]["x"]);
                double y = config.getDoubleFromSetting(primitives["spheres"][i]["y"]);
                double z = config.getDoubleFromSetting(primitives["spheres"][i]["z"]);
                std::unique_ptr<Math::Point3D> position = this->factory.createPlugin<Point3DSignature>("Point3D", x, y, z);
                double radius = config.getDoubleFromSetting(primitives["spheres"][i]["r"]);
                std::unique_ptr<Render::Color> primitiveColor = this->factory.createPlugin<ColorSignature>(
                    "Color",
                    config.getDoubleFromSetting(primitives["spheres"][i]["color"]["r"]),
                    config.getDoubleFromSetting(primitives["spheres"][i]["color"]["g"]),
                    config.getDoubleFromSetting(primitives["spheres"][i]["color"]["b"]),
                    config.getDoubleFromSetting(primitives["spheres"][i]["color"]["a"])
                );

                std::unique_ptr<Primitives::Sphere> sphere = this->factory.createPlugin<SphereSignature>(
                    "Sphere",
                    *position,
                    radius,
                    *primitiveColor
                );
                this->addPrimitive(std::make_unique<Primitives::Sphere>(*sphere));
            }
        }

        if (primitives.exists("planes")) {
            for (int i = 0; i < primitives["planes"].getLength(); i++) {
                std::string axis = config.getStringFromSetting(primitives["planes"][i]["axis"]);
                double position = config.getDoubleFromSetting(primitives["planes"][i]["position"]);
                std::unique_ptr<Render::Color> primitiveColor = this->factory.createPlugin<ColorSignature>(
                    "Color",
                    config.getDoubleFromSetting(primitives["planes"][i]["color"]["r"]),
                    config.getDoubleFromSetting(primitives["planes"][i]["color"]["g"]),
                    config.getDoubleFromSetting(primitives["planes"][i]["color"]["b"]),
                    config.getDoubleFromSetting(primitives["planes"][i]["color"]["a"])
                );

                std::unique_ptr<Primitives::Plane> plane = this->factory.createPlugin<PlaneSignature>(
                    "Plane",
                    axis,
                    position,
                    *primitiveColor
                );
                this->addPrimitive(std::make_unique<Primitives::Plane>(*plane));
            }
        }

        if (primitives.exists("cones")) {
            for (int i = 0; i < primitives["cones"].getLength(); i++) {
                double x_center = config.getDoubleFromSetting(primitives["cones"][i]["center"]["x"]);
                double y_center = config.getDoubleFromSetting(primitives["cones"][i]["center"]["y"]);
                double z_center = config.getDoubleFromSetting(primitives["cones"][i]["center"]["z"]);
                std::unique_ptr<Math::Point3D> center = this->factory.createPlugin<Point3DSignature>("Point3D", x_center, y_center, z_center);
                double x_axis = config.getDoubleFromSetting(primitives["cones"][i]["axis"]["x"]);
                double y_axis = config.getDoubleFromSetting(primitives["cones"][i]["axis"]["y"]);
                double z_axis = config.getDoubleFromSetting(primitives["cones"][i]["axis"]["z"]);
                std::unique_ptr<Math::Vector3D> axis = this->factory.createPlugin<Vector3DSignature>("Vector3D", x_axis, y_axis, z_axis);
                double base_radius = config.getDoubleFromSetting(primitives["cones"][i]["base_radius"]);
                double apex_radius = config.getDoubleFromSetting(primitives["cones"][i]["apex_radius"]);
                double height = config.getDoubleFromSetting(primitives["cones"][i]["height"]);
                // std::unique_ptr<Render::Color> primitiveColor = this->factory.createPlugin<ColorSignature>(
                //     "Color",
                //     config.getDoubleFromSetting(primitives["cone"][i]["color"]["r"]),
                //     config.getDoubleFromSetting(primitives["cone"][i]["color"]["g"]),
                //     config.getDoubleFromSetting(primitives["cone"][i]["color"]["b"]),
                //     config.getDoubleFromSetting(primitives["cone"][i]["color"]["a"])
                // );

                std::unique_ptr<Primitives::Cone> cone = this->factory.createPlugin<ConeSignature>(
                    "Cone",
                    *center,
                    *axis,
                    base_radius,
                    apex_radius,
                    height
                );
                this->addPrimitive(std::make_unique<Primitives::Cone>(*cone));
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
                std::unique_ptr<Math::Point3D> origin = this->factory.createPlugin<Point3DSignature>("Point3D", x_point, y_point, z_point);
                std::unique_ptr<Math::Vector3D> direction = this->factory.createPlugin<Vector3DSignature>("Vector3D", -x_vector, y_vector, z_vector);
                std::unique_ptr<Render::Color> lightColor = this->factory.createPlugin<ColorSignature>(
                    "Color",
                    config.getDoubleFromSetting(lights_config["directional"][i]["color"]["r"]),
                    config.getDoubleFromSetting(lights_config["directional"][i]["color"]["g"]),
                    config.getDoubleFromSetting(lights_config["directional"][i]["color"]["b"]),
                    config.getDoubleFromSetting(lights_config["directional"][i]["color"]["a"])
                );

                std::unique_ptr<Lights::DirectionalLight> light = this->factory.createPlugin<DirectionalLightSignature>(
                    "DirectionalLight",
                    *origin,
                    *direction,
                    brightness,
                    *lightColor
                );
                this->addLight(std::make_unique<Lights::DirectionalLight>(*light));
            }
        }
        if (lights_config.exists("ambient")) {
            for (int i = 0; i < lights_config["ambient"].getLength(); i++) {
                double brightness = config.getDoubleFromSetting(lights_config["ambient"][i]["brightness"]);
                std::unique_ptr<Render::Color> lightColor = this->factory.createPlugin<ColorSignature>(
                    "Color",
                    config.getDoubleFromSetting(lights_config["ambient"][i]["color"]["r"]),
                    config.getDoubleFromSetting(lights_config["ambient"][i]["color"]["g"]),
                    config.getDoubleFromSetting(lights_config["ambient"][i]["color"]["b"]),
                    config.getDoubleFromSetting(lights_config["ambient"][i]["color"]["a"])
                );

                std::unique_ptr<Lights::AmbientLight> light = this->factory.createPlugin<AmbientLightSignature>(
                    "AmbientLight",
                    brightness,
                    *lightColor
                );
                this->addLight(std::make_unique<Lights::AmbientLight>(*light));
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(84);
    }
}

RayTracer::Scene::Scene() :
    factory()
{
    this->addPrimitive(std::make_unique<Primitives::Sphere>(
        Math::Point3D(0, 0, 4),
        1,
        Render::Color(1, 0, 0, 1)
    ));

    this->addPrimitive(std::make_unique<Primitives::Sphere>(
        Math::Point3D(-1, 0, 4),
        0.5,
        Render::Color(0, 1, 0, 1)
    ));

    this->addLight(std::make_unique<Lights::DirectionalLight>(
        Math::Point3D(0.5, 0.5, 4),
        Math::Vector3D(-0.5, -0.5, 0),
        0.25,
        Render::Color(1, 1, 1, 1)
    ));

    this->addLight(std::make_unique<Lights::DirectionalLight>(
        Math::Point3D(-0.5, 0.5, 4),
        Math::Vector3D(0.5, -0.5, 0),
        1,
        Render::Color(1, 1, 1, 1)
    ));

    this->addLight(std::make_unique<Lights::AmbientLight>(
        0.1,
        Render::Color(1, 1, 1, 1)
    ));
}

RayTracer::Scene::~Scene()
{
}

void RayTracer::Scene::addPrimitive(std::unique_ptr<IPrimitives> primitive)
{
    this->primitives.push_back(std::move(primitive));
}

void RayTracer::Scene::addLight(std::unique_ptr<ILights> light)
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
            auto &sortedPrimitives = primitives;

            std::sort(sortedPrimitives.begin(), sortedPrimitives.end(), [&ray](
                std::unique_ptr<IPrimitives> const &a, std::unique_ptr<IPrimitives> const &b) {
                double distA = a->getIntersectionPoint(ray);
                double distB = b->getIntersectionPoint(ray);
                return std::abs(distA - distB) < std::numeric_limits<double>::epsilon() ? false : distA < distB;
            });

            for (std::unique_ptr<IPrimitives> &primitive : sortedPrimitives) {
                if (primitive->hits(ray)) {
                    color = primitive->computeColor(ray, this->lights);
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

void RayTracer::Scene::resetCamera()
{
    View::Camera newCamera = *this->original_camera;
    this->setCamera(std::make_unique<View::Camera>(newCamera));
}

RayTracer::Factory RayTracer::Scene::getFactory() const
{
    return this->factory;
}
