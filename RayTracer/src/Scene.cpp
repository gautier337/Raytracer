/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Scene
*/

#include "Scene.hpp"
#include <algorithm>
#include <iostream>

RayTracer::Scene::Scene(const ParseConfig &config) :
    lightsLoader("plugins/raytracer_lights.so"),
    primitivesLoader("plugins/raytracer_primitives.so"),
    mathLoader("plugins/raytracer_math.so"),
    renderLoader("plugins/raytracer_render.so"),
    viewLoader("plugins/raytracer_view.so")
{
    this->initFactories();

    auto &camera_config = config.get_setting("camera");
    if (camera_config.exists("position")) {
        double x = config.getDoubleFromSetting(camera_config["position"]["x"]);
        double y = config.getDoubleFromSetting(camera_config["position"]["y"]);
        double z = config.getDoubleFromSetting(camera_config["position"]["z"]);
        std::unique_ptr<Math::Point3D> position = this->mathFactory->createPoint3D(x, y, z);
        std::unique_ptr<Math::Point3D> origin = this->mathFactory->createPoint3D(-0.5, -0.5, 1);
        std::unique_ptr<Math::Vector3D> bottom_side = this->mathFactory->createVector3D(1, 0, 0);
        std::unique_ptr<Math::Vector3D> left_side = this->mathFactory->createVector3D(0, 1, 0);
        std::unique_ptr<Render::Color> color = this->renderFactory->createColor(0, 0, 0, 0);
        std::unique_ptr<Primitives::Rectangle3D> screen = this->primitivesFactory->createRectangle3D(
            *origin,
            *bottom_side,
            *left_side,
            *color
        );
        this->camera = this->viewFactory->createCamera(*position, *screen);
    }

    auto &primitives = config.get_setting("primitives");
    if (primitives.exists("spheres")) {
        for (int i = 0; i < primitives["spheres"].getLength(); i++) {
            double x = config.getDoubleFromSetting(primitives["spheres"][i]["x"]);
            double y = config.getDoubleFromSetting(primitives["spheres"][i]["y"]);
            double z = config.getDoubleFromSetting(primitives["spheres"][i]["z"]);
            std::unique_ptr<Math::Point3D> position = this->mathFactory->createPoint3D(x, y, z);
            double radius = config.getDoubleFromSetting(primitives["spheres"][i]["r"]);
            std::unique_ptr<Render::Color> primitiveColor = this->renderFactory->createColor(
                config.getDoubleFromSetting(primitives["spheres"][i]["color"]["r"]),
                config.getDoubleFromSetting(primitives["spheres"][i]["color"]["g"]),
                config.getDoubleFromSetting(primitives["spheres"][i]["color"]["b"]),
                config.getDoubleFromSetting(primitives["spheres"][i]["color"]["a"])
            );

            std::unique_ptr<Primitives::Sphere> sphere = this->primitivesFactory->createSphere(
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
            std::unique_ptr<Math::Point3D> origin = this->mathFactory->createPoint3D(x_point, y_point, z_point);
            std::unique_ptr<Math::Vector3D> direction = this->mathFactory->createVector3D(-x_vector, y_vector, z_vector);
            std::unique_ptr<Render::Color> lightColor = this->renderFactory->createColor(
                config.getDoubleFromSetting(lights_config["directional"][i]["color"]["r"]),
                config.getDoubleFromSetting(lights_config["directional"][i]["color"]["g"]),
                config.getDoubleFromSetting(lights_config["directional"][i]["color"]["b"]),
                config.getDoubleFromSetting(lights_config["directional"][i]["color"]["a"])
            );

            std::unique_ptr<Lights::DirectionalLight> light = this->lightsFactory->createDirectionalLight(
                *origin,
                *direction,
                brightness,
                *lightColor
            );
            this->addLight(std::make_shared<Lights::DirectionalLight>(*light));
        }
    }

    std::unique_ptr<Math::Point3D> origin = this->mathFactory->createPoint3D(0, -5000, 0);
    std::unique_ptr<Math::Vector3D> bottom_side = this->mathFactory->createVector3D(0, 10000, 10000);
    std::unique_ptr<Math::Vector3D> left_side = this->mathFactory->createVector3D(0, 0, 0);
    std::unique_ptr<Render::Color> color = this->renderFactory->createColor(1, 1, 0, 1);
    std::unique_ptr<Primitives::Rectangle3D> ground = this->primitivesFactory->createRectangle3D(
        *origin,
        *bottom_side,
        *left_side,
        *color
    );
    this->addPrimitive(std::make_shared<Primitives::Rectangle3D>(*ground));
}

RayTracer::Scene::Scene() :
    lightsLoader("plugins/raytracer_lights.so"),
    primitivesLoader("plugins/raytracer_primitives.so"),
    mathLoader("plugins/raytracer_math.so"),
    renderLoader("plugins/raytracer_render.so"),
    viewLoader("plugins/raytracer_view.so")
{
    this->initFactories();
}

RayTracer::Scene::~Scene()
{
}

void RayTracer::Scene::initFactories()
{
    std::string const &createLightsFn = "createLightsFactory";
    std::string const &createMathFn = "createMathFactory";
    std::string const &createPrimitivesFn = "createPrimitivesFactory";
    std::string const &createRenderFn = "createRenderFactory";
    std::string const &createViewFn = "createViewFactory";

    using lightsFnPtr = std::unique_ptr<Lights::LightsFactory> (*)();
    using mathFnPtr = std::unique_ptr<Math::MathFactory> (*)();
    using primitivesFnPtr = std::unique_ptr<Primitives::PrimitivesFactory> (*)();
    using renderFnPtr = std::unique_ptr<Render::RenderFactory> (*)();
    using viewFnPtr = std::unique_ptr<View::ViewFactory> (*)();

    lightsFnPtr createLightsPtr = this->lightsLoader.template getInstance<lightsFnPtr>(createLightsFn);
    mathFnPtr createMathPtr = this->mathLoader.template getInstance<mathFnPtr>(createMathFn);
    primitivesFnPtr createPrimitivesPtr = this->primitivesLoader.template getInstance<primitivesFnPtr>(createPrimitivesFn);
    renderFnPtr createRenderPtr = this->renderLoader.template getInstance<renderFnPtr>(createRenderFn);
    viewFnPtr createViewPtr = this->viewLoader.template getInstance<viewFnPtr>(createViewFn);

    try {
        this->lightsFactory = createLightsPtr();
        this->mathFactory = createMathPtr();
        this->primitivesFactory = createPrimitivesPtr();
        this->renderFactory = createRenderPtr();
        this->viewFactory = createViewPtr();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
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

std::unique_ptr<RayTracer::Math::MathFactory> RayTracer::Scene::getMathFactory()
{
    return std::move(this->mathFactory);
}
