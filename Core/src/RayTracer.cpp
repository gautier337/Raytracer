/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Raytracer
*/

#include "RayTracer.hpp"
#include "Vector3D.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Color.hpp"
#include "Signatures.hpp"
#include "parse_config.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include <memory>

int raytracer(std::string const &sceneFile)
{
    ParseConfig config(sceneFile);
    std::vector<int> window_height_width;
    int screenHeight = 0;
    int screenWidth = 0;

    try {
        window_height_width = config.get_window_height_width_from_setting();
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return ERROR;
    }
    screenHeight = window_height_width[1];
    screenWidth = window_height_width[0];

    RayTracer::Scene scene(config);
    RayTracer::Factory factory = scene.getFactory();
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Raytracer", sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Event event;
    bool shouldUpdatePoints = true;

    std::vector<sf::RectangleShape> points;
    const int pixelSize = 5;
    const int numPixels = (screenWidth / pixelSize) * (screenHeight / pixelSize);

    for (int i = 0; i < numPixels; i++) {
        sf::RectangleShape point(sf::Vector2f(pixelSize, pixelSize * pixelSize));
        point.setPosition((i % screenHeight) * pixelSize, (i / screenHeight) * pixelSize * pixelSize);
        points.push_back(point);
    }

    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                shouldUpdatePoints = true;
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::Z:
                        scene.translateCamera(*factory.createPlugin<Vector3DSignature>("Vector3D", 0, 0, 0.5));
                        break;
                    case sf::Keyboard::S:
                        scene.translateCamera(*factory.createPlugin<Vector3DSignature>("Vector3D", 0, 0, -0.5));
                        break;
                    case sf::Keyboard::Q:
                        scene.translateCamera(*factory.createPlugin<Vector3DSignature>("Vector3D", -0.5, 0, 0));
                        break;
                    case sf::Keyboard::D:
                        scene.translateCamera(*factory.createPlugin<Vector3DSignature>("Vector3D", 0.5, 0, 0));
                        break;
                    case sf::Keyboard::Space:
                        scene.translateCamera(*factory.createPlugin<Vector3DSignature>("Vector3D", 0, 0.5, 0));
                        break;
                    case sf::Keyboard::LShift:
                        scene.translateCamera(*factory.createPlugin<Vector3DSignature>("Vector3D", 0, -0.5, 0));
                        break;
                shouldUpdatePoints = true;
                    case sf::Keyboard::Up:
                        scene.rotateCamera(*factory.createPlugin<Vector3DSignature>("Vector3D", -1, 0, 0), 0.1);
                        break;
                    case sf::Keyboard::Down:
                        scene.rotateCamera(*factory.createPlugin<Vector3DSignature>("Vector3D", 1, 0, 0), 0.1);
                        break;
                    case sf::Keyboard::Left:
                        scene.rotateCamera(*factory.createPlugin<Vector3DSignature>("Vector3D", 0, -1, 0), 0.1);
                        break;
                    case sf::Keyboard::Right:
                        scene.rotateCamera(*factory.createPlugin<Vector3DSignature>("Vector3D", 0, 1, 0), 0.1);
                        break;
                    case sf::Keyboard::R:
                        scene.resetCamera();
                        break;
                    default:
                        break;
                }
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("RayTracer");
        ImGui::Text("Camera position: %f %f %f",
            scene.getCamera().getOrigin().getX(),
            scene.getCamera().getOrigin().getY(),
            scene.getCamera().getOrigin().getZ()
        );

        ImGui::Button("Reset Camera");
        if (ImGui::IsItemClicked()) {
            shouldUpdatePoints = true;
            scene.resetCamera();
        }

        for (auto &primitive : scene.getPrimitives()) {
            RayTracer::Render::Color primitiveColor = primitive->getColor();
            float color[4] = {
                (float)primitiveColor.getR(),
                (float)primitiveColor.getG(),
                (float)primitiveColor.getB(),
                (float)primitiveColor.getA()
            };
            ImGui::ColorEdit3(primitive->getType().c_str(), color);
            if (memcmp(&color, &primitiveColor, sizeof(float) * 4) != 0) {
                shouldUpdatePoints = true;
                primitive->setColor(
                    RayTracer::Render::Color(
                        static_cast<double>(color[0]),
                        static_cast<double>(color[1]),
                        static_cast<double>(color[2]),
                        static_cast<double>(color[3])
                    )
                );
            }
        }
        ImGui::End();

        scene.render(pixelSize, screenWidth, screenHeight);
        std::vector<std::vector<RayTracer::Render::Color>> pixels = scene.getPixels();
        int nb_rows = pixels.size();
        if (shouldUpdatePoints) {
            int index = 0;
            for (double y = 0; y < 1; y += static_cast<double>(pixelSize) / screenHeight) {
                for (double x = 0; x < 1; x += static_cast<double>(pixelSize) / screenWidth) {
                    sf::Color color(
                        pixels[index / nb_rows][index % nb_rows].getR() * 255,
                        pixels[index / nb_rows][index % nb_rows].getG() * 255,
                        pixels[index / nb_rows][index % nb_rows].getB() * 255,
                        255
                    );
                    points[index].setFillColor(color);
                    index += 1;
                }
            }
            shouldUpdatePoints = false;
        }

        window.clear();
        for (const auto &point : points)
            window.draw(point);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return SUCCESS;
}
