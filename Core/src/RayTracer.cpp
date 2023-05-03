/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Raytracer
*/

#include "RayTracer.hpp"
#include "IFactory.hpp"
#include "Vector3D.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Color.hpp"
#include "parse_config.hpp"
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
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Raytracer", sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Event event;
    bool shouldUpdatePoints = true;

    std::vector<sf::RectangleShape> points;
    const int pixelSize = 1;
    const int numPixels = (screenWidth / pixelSize) * (screenHeight / pixelSize);

    for (int i = 0; i < numPixels; i++) {
        sf::RectangleShape point(sf::Vector2f(pixelSize, pixelSize));
        point.setPosition((i % screenHeight) * pixelSize, (i / screenHeight) * pixelSize);
        points.push_back(point);
    }

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                shouldUpdatePoints = true;
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::Z:
                        scene.translateCamera(RayTracer::Math::Vector3D(0, 0, 0.5));
                        break;
                    case sf::Keyboard::S:
                        scene.translateCamera(RayTracer::Math::Vector3D(0, 0, -0.5));
                        break;
                    case sf::Keyboard::Q:
                        scene.translateCamera(RayTracer::Math::Vector3D(-0.5, 0, 0));
                        break;
                    case sf::Keyboard::D:
                        scene.translateCamera(RayTracer::Math::Vector3D(0.5, 0, 0));
                        break;
                    case sf::Keyboard::Space:
                        scene.translateCamera(RayTracer::Math::Vector3D(0, 0.5, 0));
                        break;
                    case sf::Keyboard::LShift:
                        scene.translateCamera(RayTracer::Math::Vector3D(0, -0.5, 0));
                        break;
                shouldUpdatePoints = true;
                    case sf::Keyboard::Up:
                        scene.rotateCamera(RayTracer::Math::Vector3D(-1, 0, 0), 0.1);
                        break;
                    case sf::Keyboard::Down:
                        scene.rotateCamera(RayTracer::Math::Vector3D(1, 0, 0), 0.1);
                        break;
                    case sf::Keyboard::Left:
                        scene.rotateCamera(RayTracer::Math::Vector3D(0, -1, 0), 0.1);
                        break;
                    case sf::Keyboard::Right:
                        scene.rotateCamera(RayTracer::Math::Vector3D(0, 1, 0), 0.1);
                        break;
                    default:
                        break;
                }
            }
        }
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
        window.display();
    }
    return SUCCESS;
}
