/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Raytracer
*/

#include "Raytracer.hpp"
#include "IFactory.hpp"
#include "Vector3D.hpp"
#include "Factory.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "Cylinder.hpp"
#include "Ray.hpp"
#include <memory>

int raytracer_cylinder(std::string const &sceneFile)
{
    RayTracer::Camera cam(Math::Point3D(0, 0, 0), RayTracer::Rectangle3D(Math::Point3D(-0.5, -0.5, 1), Math::Vector3D(1, 0, 0), Math::Vector3D(0, 1, 0)));
    RayTracer::Cylinder cyl(Math::Point3D(0, 0, 2), Math::Vector3D(0, 1, 0), 0.25, 1);
    RayTracer::Rectangle3D ground(Math::Point3D(0, -500, 0), Math::Vector3D(0, 1000, 1000), Math::Vector3D(0, 0, 0));
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Raytracer", sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Event event;
    bool shouldUpdatePoints = true;

    std::vector<sf::RectangleShape> points;
    const int pixelSize = 1;
    const int screenSize = 1000;
    const int numPixels = screenSize / pixelSize;

    for (int i = 0; i < numPixels * numPixels; i++) {
        sf::RectangleShape point(sf::Vector2f(pixelSize, pixelSize));
        point.setPosition((i % numPixels) * pixelSize, (i / numPixels) * pixelSize);
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
                        cam.translate(Math::Vector3D(0, 0, 0.05));
                        break;
                    case sf::Keyboard::S:
                        cam.translate(Math::Vector3D(0, 0, -0.05));
                        break;
                    case sf::Keyboard::Q:
                        cam.translate(Math::Vector3D(-0.05, 0, 0));
                        break;
                    case sf::Keyboard::D:
                        cam.translate(Math::Vector3D(0.05, 0, 0));
                        break;
                    case sf::Keyboard::Space:
                        cam.translate(Math::Vector3D(0, 0.05, 0));
                        break;
                    case sf::Keyboard::LControl:
                        cam.translate(Math::Vector3D(0, -0.05, 0));
                        break;
                    default:
                        break;
                }
            }
        }
        if (shouldUpdatePoints) {
            int index = 0;
            for (double y = 1; y >= 0; y -= static_cast<double>(pixelSize) / screenSize) {
                for (double x = 0; x < 1; x += static_cast<double>(pixelSize) / screenSize) {
                    double u = x;
                    double v = y;
                    RayTracer::Ray r = cam.ray(u, v);
                    if (cyl.hits(r))
                        points[index].setFillColor(sf::Color::Red);
                    else if (ground.hits(r))
                        points[index].setFillColor(sf::Color::Green);
                    else
                        points[index].setFillColor(sf::Color::Black);
                    index += 1;
                }
            }
            shouldUpdatePoints = false;
        }
        window.clear();
        for (const auto &point : points) {
            window.draw(point);
        }
        window.display();
    }
    return SUCCESS;
}
