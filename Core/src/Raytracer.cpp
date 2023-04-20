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
#include "Ray.hpp"
#include <memory>

int raytracer(std::string const &sceneFile)
{
    RayTracer::Camera cam(Math::Point3D(0, 0, 0), RayTracer::Rectangle3D(Math::Point3D(-0.5, -0.5, 1), Math::Vector3D(1, 0, 0), Math::Vector3D(0, 1, 0)));
    RayTracer::Sphere s(Math::Point3D(0, 0, 2), 0.5);
    RayTracer::Rectangle3D ground(Math::Point3D(0, -500, 0), Math::Vector3D(0, 1000, 1000), Math::Vector3D(0, 0, 0));
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Raytracer", sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Event event;

    /* std::cout << "P3" << std::endl;
    std::cout << "100 100" << std::endl;
    std::cout << "255" << std::endl;
    for (double y = 1; y >= 0; y -= 0.010) {
        for (double x = 0; x < 1; x += 0.010) {
            double u = x;
            double v = y;
            RayTracer::Ray r = cam.ray(u, v);
            if (s.hits(r)) {
                std::cout << "255 0 0" << std::endl;
            } else if (ground.hits(r)) {
                std::cout << "0 255 0" << std::endl;
            } else {
                std::cout << "0 0 0" << std::endl;
            }
        }
    } */
    std::vector<sf::RectangleShape> points;
    for (int i = 0; i < 1000 * 1000; i++) {
        sf::RectangleShape point(sf::Vector2f(1, 1));
        point.setPosition(i % 1000, i / 1000);
        points.push_back(point);
    }
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::Left:
                        s.translate(Math::Vector3D(-0.05, 0, 0));
                        break;
                    case sf::Keyboard::Right:
                        s.translate(Math::Vector3D(0.05, 0, 0));
                        break;
                    case sf::Keyboard::Up:
                        s.translate(Math::Vector3D(0, 0.05, 0));
                        break;
                    case sf::Keyboard::Down:
                        s.translate(Math::Vector3D(0, -0.05, 0));
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
        window.clear();
        int index = 0;
        for (double y = 1; y >= 0; y -= 0.001) {
            for (double x = 0; x < 1; x += 0.001) {
                double u = x;
                double v = y;
                RayTracer::Ray r = cam.ray(u, v);
                if (s.hits(r))
                    points[index].setFillColor(sf::Color::Red);
                else if (ground.hits(r))
                    points[index].setFillColor(sf::Color::Green);
                else
                    points[index].setFillColor(sf::Color::Black);
                window.draw(points[index]);
                index += 1;
            }
        }
        window.display();
    }
    return SUCCESS;
}
